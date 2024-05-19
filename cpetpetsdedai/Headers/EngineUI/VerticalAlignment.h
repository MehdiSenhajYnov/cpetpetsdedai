#pragma once
#include "AlignmentBase.h"

class VerticalAlignment : public AlignmentBase
{
public:
	ADD_TYPE(VerticalAlignment, AlignmentBase, REG_TYPE)
	VerticalAlignment() : AlignmentBase("VerticalAlignment", AlignmentBase::GetStaticType()) {}
	
	void UpdatePositionOfElement(EngineUIElement* _elementInstance, int _index) override;

};


