#include "stdafx.h"
#include "AppCore.h"
#include "BubbleExternalSort.h"

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
	if (file->checkForEquality()) {
		return Responce::InputAndOutputIsEqual;
	}
	ExternalMergeSort *s=nullptr;
	switch (type) {
	case Bubble:
		s = new BubbleExternalSort();
		s->setParams(file, sizeOfSegments);
	}
	this->type = type;
	sort = s;
	return Responce::Success;
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
