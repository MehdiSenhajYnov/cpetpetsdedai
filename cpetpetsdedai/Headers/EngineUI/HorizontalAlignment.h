#pragma once
#include "AlignmentBase.h"

class HorizontalAlignment : public AlignmentBase
{
public:
    ADD_TYPE(HorizontalAlignment, AlignmentBase, REG_TYPE)
    HorizontalAlignment() : AlignmentBase("HorizontalAlignment", AlignmentBase::GetStaticType()) {}
	
    void UpdatePositionOfElement(EngineUIElement* _elementInstance, int _index) override;
};
