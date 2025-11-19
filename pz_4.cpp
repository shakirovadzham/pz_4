#include <iostream>
#include <algorithm>
using namespace std;

class DynamicArray {
protected:
    int *elements;
    int arraySize;

public:
    DynamicArray(int initialSize) {
        if (initialSize < 0) {
            cout << "Error: Array size cannot be negative" << endl;
            arraySize = 0;
            elements = nullptr;
            return;
        }
        arraySize = initialSize;
        elements = new int[arraySize];
        for (int i = 0; i < arraySize; i++) {
            elements[i] = 0; 
        }
    }

    DynamicArray(const DynamicArray& source) {
        arraySize = source.arraySize;
        elements = new int[arraySize];
        for (int i = 0; i < arraySize; i++) {
            elements[i] = source.elements[i];
        }
    }

    ~DynamicArray() {
        delete[] elements;
    }

    void assignElement(int position, int newValue) {
        if (0 <= position && position < arraySize) {
            if (-100 <= newValue && newValue <= 100) {
                elements[position] = newValue;
            } else {
                cout << "Error: Value " << newValue << " exceeds allowed range [-100, 100]" << endl;
            }
        } else {
            cout << "Error: Position " << position << " is outside array bounds" << endl;
        }
    }

    int retrieveElement(int position) {
        if (0 <= position && position < arraySize) {
            return elements[position];
        } else {
            cout << "Error: Position " << position << " is outside array bounds" << endl;
            return 0;
        }
    }

    void displayContents() {
        for (int i = 0; i < arraySize; i++) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }

    void appendElement(int newValue) {
        if (-100 <= newValue && newValue <= 100) {
            int* extendedArray = new int[arraySize + 1];
            
            for (int i = 0; i < arraySize; i++) {
                extendedArray[i] = elements[i];
            }
            
            extendedArray[arraySize] = newValue;
            
            delete[] elements;
            elements = extendedArray;
            arraySize += 1;
        } else {
            cout << "Error: Value " << newValue << " exceeds allowed range [-100, 100]" << endl;
        }
    }

    DynamicArray combineArrays(const DynamicArray& secondArray) {
        int largerSize = (arraySize > secondArray.arraySize) ? arraySize : secondArray.arraySize;
        DynamicArray combinedArray(largerSize);
        
        for (int i = 0; i < largerSize; i++) {
            int firstVal = (i < arraySize) ? elements[i] : 0;
            int secondVal = (i < secondArray.arraySize) ? secondArray.elements[i] : 0;
            combinedArray.elements[i] = firstVal + secondVal;
        }
        
        return combinedArray;
    }

    DynamicArray subtractArrays(const DynamicArray& secondArray) {
        int largerSize = (arraySize > secondArray.arraySize) ? arraySize : secondArray.arraySize;
        DynamicArray differenceArray(largerSize);
        
        for (int i = 0; i < largerSize; i++) {
            int firstVal = (i < arraySize) ? elements[i] : 0;
            int secondVal = (i < secondArray.arraySize) ? secondArray.elements[i] : 0;
            differenceArray.elements[i] = firstVal - secondVal;
        }
        
        return differenceArray;
    }

    int getArraySize() const {
        return arraySize;
    }
};

class ArrayAnalyzer : public DynamicArray {
public:
    using DynamicArray::DynamicArray;
    
    void showCalculationMessage() {
        cout << "Calculating median value..." << endl;
    }

    void displayMedian() {
        showCalculationMessage();
        ArrayAnalyzer temporaryCopy(*this);
        sort(temporaryCopy.elements, temporaryCopy.elements + temporaryCopy.arraySize);
        if (temporaryCopy.arraySize == 0) {
            cout << "Array is empty" << endl;
            return;
        }
        double medianResult;
        if (temporaryCopy.arraySize % 2 == 0) {
            medianResult = (temporaryCopy.elements[temporaryCopy.arraySize / 2 - 1] + 
                           temporaryCopy.elements[temporaryCopy.arraySize / 2]) / 2.0;
        } else {
            medianResult = temporaryCopy.elements[temporaryCopy.arraySize / 2];
        }
        cout << "Median value: " << medianResult << endl;
    }

    void displayAverage() {
        if (arraySize == 0) {
            cout << "Array is empty" << endl;
            return;
        }
        double sum = 0.0;
        for (int i = 0; i < arraySize; i++) { 
            sum += elements[i];
        }
        cout << "Average value: " << sum / arraySize << endl;
    }

    int findMinimum() {
        if (arraySize == 0) {
            cout << "Array is empty" << endl;
            return 0;
        }
        int minimum = elements[0];
        for (int i = 1; i < arraySize; i++) {
            if (minimum > elements[i]) {
                minimum = elements[i];
            }
        }
        cout << "Minimum value: " << minimum << endl;
        return minimum;
    }

    int findMaximum() {
        if (arraySize == 0) {
            cout << "Array is empty" << endl;
            return 0;
        }
        int maximum = elements[0];
        for (int i = 1; i < arraySize; i++) {
            if (maximum < elements[i]) {
                maximum = elements[i];
            }
        }
        cout << "Maximum value: " << maximum << endl;
        return maximum;
    }
};

int main() {
    cout << "Creating array A with 3 elements:" << endl;
    DynamicArray arrayA(3);
    arrayA.assignElement(0, 10);
    arrayA.assignElement(1, 20);
    arrayA.assignElement(2, 30);
    cout << "Array A: ";
    arrayA.displayContents();

    cout << "\nCreating array B with 5 elements:" << endl;
    DynamicArray arrayB(5);
    arrayB.assignElement(0, 5);
    arrayB.assignElement(1, 15);
    arrayB.assignElement(2, 25);
    arrayB.assignElement(3, 35);
    arrayB.assignElement(4, 45);
    cout << "Array B: ";
    arrayB.displayContents();

    cout << "\nTesting copy constructor:" << endl;
    DynamicArray arrayC = arrayA;
    cout << "Array C (copy of A): ";
    arrayC.displayContents();

    cout << "\nAdding value 40 to array A:" << endl;
    arrayA.appendElement(40);
    cout << "Array A after addition: ";
    arrayA.displayContents();

    cout << "\nAdding arrays A and B:" << endl;
    DynamicArray sumArray = arrayA.combineArrays(arrayB);
    cout << "A + B: ";
    sumArray.displayContents();

    cout << "\nSubtracting arrays A and B:" << endl;
    DynamicArray diffArray = arrayA.subtractArrays(arrayB);
    cout << "A - B: ";
    diffArray.displayContents();

    cout << "\nTesting error handling:" << endl;
    arrayA.assignElement(10, 50);
    arrayA.assignElement(0, 150);

    cout << "\n=== ARRAY STATISTICS ===" << endl;
    
    cout << "\nAnalyzing array A:" << endl;
    
    ArrayAnalyzer analyzer1(3);
    analyzer1.assignElement(0, 10);
    analyzer1.assignElement(1, 20);
    analyzer1.assignElement(2, 30);
    
    cout << "Analyzer1 array: ";
    analyzer1.displayContents();
    analyzer1.displayMedian();
    analyzer1.displayAverage();
    analyzer1.findMinimum();
    analyzer1.findMaximum();
    
    ArrayAnalyzer analyzer2(5);
    analyzer2.assignElement(0, 5);
    analyzer2.assignElement(1, 15);
    analyzer2.assignElement(2, 25);
    analyzer2.assignElement(3, 35);
    analyzer2.assignElement(4, 45);
    
    cout << "\nAnalyzer2 array: ";
    analyzer2.displayContents();
    analyzer2.displayMedian();
    analyzer2.displayAverage();
    analyzer2.findMinimum();
    analyzer2.findMaximum();

    return 0;
}