#include "stdafx.h"
#include "AppCore.h"
#include "BubbleExternalSort.h"
#include "QuickExternalSort.h"

Responce AppCore::setSortParams(FileManager *file, long long sizeOfSegments, TypeOfSort type)
{
	if (file->getState() != ReadAndWrite) {
		this->type = Fail;
		return Responce::FileManagerFail;
	}
	if (sizeOfSegments < 0) {
		this->type = Fail;
		return Responce::SizeError;
	}
	if (sizeOfSegments%2==1) {
		this->type = Fail;
		return Responce::SizeError;
	}
	if (file->checkForEquality()) {
		return Responce::InputAndOutputIsEqual;
	}
	ExternalMergeSort *s=nullptr;
	switch (type) {
	case Bubble:
		s = new BubbleExternalSort();
		s->setParams(file, sizeOfSegments);
		break;
	case Quick:
		s = new QuickExternalSort();
		s->setParams(file, sizeOfSegments);
		break;
	}
	this->type = type;
	sort = s;
	return Responce::Success;
}

Responce AppCore::externalSort()
{
	if (sort == nullptr) {
		return Responce::ParamsFail;
	}
	return sort->externalSort();
}

Counter AppCore::getCounter()
{
	return sort->counter;
}

AppCore::AppCore()
{
	sort = nullptr;
	type = Fail;
}


AppCore::~AppCore()
{
	if (sort != nullptr) {
		free(sort);
	}
}
