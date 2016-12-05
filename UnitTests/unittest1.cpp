#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ExternalMergeSortProduction/FileManager.h"
#include "../ExternalMergeSortProduction/Counter.h"
#include "../ExternalMergeSortProduction/ExternalMergeSort.h"
#include "../ExternalMergeSortProduction/BubbleExternalSort.h"
#include "../ExternalMergeSortProduction/HeapExternalSort.h"
#include "../ExternalMergeSortProduction/QuickExternalSort.h"
#include <map>
#include "../ExternalMergeSortProduction/Structures.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{		


	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(checkBubbleSort)
		{
			long long sizeOfSegments = 100;
			FileManager *file = new FileManager("input.txt", "output.txt");
			/*file->generateSequence(10000, Average);*/
			/*map<long, long> sourceMap;
			long long source[10000];
			long long size = 10000;
			long long *readCount = new long long();
			file->read(source, 10000, readCount);
			Assert::IsTrue(size == *readCount);
			
			long long count = 0;
			for (int i = 0; i < 10000; i++) {
				count = sourceMap[source[i]] + 1;
				sourceMap.insert(pair<long , long >(source[i], count));
			}

			BubbleExternalSort *sort = new BubbleExternalSort();
			sort->setParams(file, sizeOfSegments);

			FileManager *dest = new FileManager("output.txt", ReadOnly);
			long long result[10000];
			*readCount = 0;
			dest->read(result, 10000, readCount);
			Assert::IsTrue(size == *readCount);


			map<long , long > resultMap;
			count = 0;
			for (int i = 0; i < 10000; i++) {
				count = resultMap[result[i]] + 1;
				resultMap.insert(pair<long , long >(result[i], count));
				if (i > 0) {
					Assert::IsTrue(result[i] >= result[i - 1]);
				}
			}

			auto it1 = resultMap.begin();
			for (auto it = sourceMap.begin(); it != sourceMap.end(); ++it)
			{
				Assert::IsTrue((*it).second == (*it1).second);
				it1++;
			}*/
		}

	};
}