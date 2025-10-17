#include "SkillSplitThunder.h"
#include "Graphics/Graphics.h"
#include "Collision/CollisionManager.h"

SkillSplitThunder::SkillSplitThunder()
    : Skill("SplitThunder", SkillManager::SkillType::SkillSplitThunder),
    collision_(new Collision(Collision::Type::Bullet, this, 30.0f))
{
}

// �X�V
void SkillSplitThunder::Update(const float& elapsedTime)
{
    Transform2D& transform = transforms_.at(0);

    // �ړ�����
    transform.AddPosition(moveDirection_ * moveSpeed_ * elapsedTime);

    // ��ʊO�ɏo���玩�g����������
    const DirectX::XMFLOAT2 minPosition = transform.GetSize() * -1.0f;
    const DirectX::XMFLOAT2 maxPosition = DirectX::XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
    const DirectX::XMFLOAT2 position = transform.GetPosition();

    if (position.x <= minPosition.x || position.y <= minPosition.y ||
        position.x >= maxPosition.x || position.y >= maxPosition.y)
    {
        SkillManager::Instance().Remove(this);
        
        // Collision�̌㏈��
        CollisionRemove();
    }

    // Object�ɂ���Transform���X�V���遦�����蔻��p
    Object::GetTransform()->SetPosition(transform.GetPosition());
}

// ImGui
void SkillSplitThunder::DrawDebug()
{
}
// ����
void SkillSplitThunder::Launch(const int& splitCount, const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& oldDirection, const float& angle)
{
    Transform2D transform = {};
    transform.SetPosition(position);
    transform.SetSize(50.0f);
    transform.SetTexSize(50.0f);
    transform.SetPivot(25.0f);

    transforms_.emplace_back(transform);

    // Object�ɂ���Transform��ݒ肷�遦�����蔻��p
    Object::GetTransform()->SetPosition(transform.GetPosition());
    Object::GetTransform()->SetSize(transform.GetSize());
    Object::GetTransform()->SetTexSize(transform.GetTexSize());
    Object::GetTransform()->SetPivot(transform.GetPivot());

    // �i�s���������肷��
    moveDirection_ =
    {
        oldDirection.x * cosf(angle) - oldDirection.y * sinf(angle),
        oldDirection.x * sinf(angle) + oldDirection.y * cosf(angle)
    };

    splitCount_ = splitCount;
}

// �Փˌ��m
void SkillSplitThunder::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
    if (type == Collision::Type::Enemy)
    {
        ++splitCount_;
        // ����񐔂ɒB����
        if (splitCount_ > maxSplint_)
        {
            // �������g�̍폜
            SkillManager::Instance().Remove(this);
            // Collision�̌㏈��
            CollisionRemove();

            return;
        }

        // �V����2��������
        SkillSplitThunder* splitThunder0 = new SkillSplitThunder();
        SkillSplitThunder* splitThunder1 = new SkillSplitThunder();
        splitThunder0->Launch(splitCount_, Object::GetTransform()->GetPosition(), moveDirection_, DirectX::XMConvertToRadians(45.0f));
        splitThunder1->Launch(splitCount_, Object::GetTransform()->GetPosition(), moveDirection_, DirectX::XMConvertToRadians(-45.0f));

        // �������g�̍폜
        SkillManager::Instance().Remove(this);
        // Collision�̌㏈��
        CollisionRemove();
    }
}

// Collision�̌㏈��
void SkillSplitThunder::CollisionRemove()
{
    CollisionManager::Instance().Remove(collision_);
    collision_ = nullptr;
}