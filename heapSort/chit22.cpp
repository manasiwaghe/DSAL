/*Read the marks obtained by students of second year in an online examination ofparticular subject.
 Find out maximum and minimum marks obtained in that subject. Use heap data structure. Analyze the algorithm.*/
#include <iostream>

using namespace std;

class Student {
private:
    int marks;

public:
    // Constructor
    Student(){}

    Student(int _marks) {
        this->marks = _marks;
    }

    // Getter for marks
    int getMarks() const {
        return marks;
    }
};

void heapify(Student arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l].getMarks() > arr[largest].getMarks())
        largest = l;

    if (r < n && arr[r].getMarks() > arr[largest].getMarks())
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(Student arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    Student* students = new Student[n];
    cout << "Enter the marks obtained by each student: ";
    for (int i = 0; i < n; ++i) {
        int marks;
        cin >> marks;
        students[i] = Student(marks);
    }

    heapSort(students, n);

    cout << "Maximum mark obtained: " << students[n - 1].getMarks() << endl;
    cout << "Minimum mark obtained: " << students[0].getMarks() << endl;

    delete[] students; // Freeing the allocated memory

    return 0;
}
