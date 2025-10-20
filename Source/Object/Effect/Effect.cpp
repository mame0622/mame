#include "Effect.h"

Effect::Effect(const std::string& name, const EffectManager::EffectType& effectType)
    : Object(name), effectType_(effectType)
{
    // ���g���}�l�[�W���[�ɓo�^
    EffectManager::Instance().Register(this);
}