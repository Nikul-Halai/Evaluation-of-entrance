// The Libararies are included here

#include <stdio.h>
#include <stdlib.h>



// I am defining Typedef here

typedef struct DataStruct DataStruct;
typedef struct Line Line;
typedef struct Class Class;

struct Class {
    long long int TimeOfArrival;
    long long int ClassSize;
    long long int TimeToPro;
    long long int Leaving;
    long long int WaitingTime;
};

struct DataStruct {
    Class data;
    DataStruct * FollowingPerson;
};


struct Line {
    DataStruct * head;
    DataStruct * tail;
};

//prototypes of the line function
Line * MakeTheLine();
void eLine(Line * line, Class data);
void dLine(Line * line, Class data);
void AddDataStructToLine(DataStruct * DataStruct, Line * LineOnLeft, Line * LineOnRight);
void DeleteDataStruct(long long int Present, Line * LineOnLeft, Line * LineOnRight);
long long int TimeUntilNextTurn(DataStruct * tail);

// Function prototypes


void classify(Class * array, int ClassSize);
DataStruct * DataSt(Class data);
DataStruct * TailAd(DataStruct * tail, Class data);
DataStruct * DeleteHead(DataStruct * tail, Class data);



int main() {
    long long int GroupCount = 0;

    scanf("%lld", &GroupCount);

    while(GroupCount < 1 || GroupCount > 500000) {

        scanf("%lld", &GroupCount);
    }

    Class * TotalGroup = (Class *) malloc(sizeof(Class) * GroupCount);

    for(int i = 0; i < GroupCount; i++) {

        // Read the data from the input
        scanf("%lld %lld %lld", &TotalGroup[i].ClassSize, &TotalGroup[i].TimeOfArrival, &TotalGroup[i].TimeToPro);

        while((TotalGroup[i].ClassSize < 1 || TotalGroup[i].ClassSize > 1000000) || (TotalGroup[i].TimeOfArrival
        < 1 || TotalGroup[i].TimeOfArrival > 1000000000) || (TotalGroup[i].TimeToPro < 1 || TotalGroup[i].TimeToPro > 1000000)) {
            scanf("%lld %lld %lld", &TotalGroup[i].ClassSize, &TotalGroup[i].TimeOfArrival, &TotalGroup[i].TimeToPro);
        }

    }

    classify(TotalGroup, GroupCount);

    DataStruct * tail = NULL;


    for(int i = 0; i < GroupCount; i++) {
        tail = TailAd(tail, TotalGroup[i]);
    }

    Line * LineOnLeft = MakeTheLine();
    Line * LineOnRight = MakeTheLine();


    for (DataStruct * temp = tail->FollowingPerson; temp != tail; temp = temp->FollowingPerson) {
        // Remove the processed nodes from the queue
        DeleteDataStruct(temp->data.TimeOfArrival, LineOnLeft, LineOnRight);

        // If the queue is empty, set the endTime to the arrivalTime + processTime
        if (LineOnLeft->tail == NULL || LineOnRight->tail == NULL) {
            temp->data.Leaving = temp->data.TimeOfArrival + temp->data.TimeToPro;
        }
        // If the queue is not empty, set the endTime to the exitTime of the last person in the queue + processTime
        else {
            // Get the exitTime of the last person in the queue
            // If the current group is going to be in left queue, get the exitTime of the last person in the left queue
            // And vice versa
            long long int TimeToLeave = 0;

            int SizeOfLineOnLeft = 0;
            int SizeOfLineOnRight = 0;

            DataStruct * LineTp = LineOnLeft->tail;
            do {
                SizeOfLineOnLeft += LineTp->data.ClassSize;
                LineTp = LineTp->FollowingPerson;
            } while (LineTp != LineOnLeft->tail);
            LineTp = LineOnRight->tail;
            do {
                SizeOfLineOnRight += LineTp->data.ClassSize;
                LineTp = LineTp->FollowingPerson;
            } while (LineTp != LineOnRight->tail);

            if(SizeOfLineOnLeft <= SizeOfLineOnRight || SizeOfLineOnLeft == SizeOfLineOnRight) {
                DataStruct * TmpTwo= LineOnLeft->tail;
                do {
                    if (TmpTwo->data.Leaving > TimeToLeave) {
                        TimeToLeave = TmpTwo->data.Leaving;
                    }
                    TmpTwo= TmpTwo->FollowingPerson;
                } while (TmpTwo!= LineOnLeft->tail);
            }
            else {
                DataStruct * TmpTwo= LineOnRight->tail;
                do {
                    if (TmpTwo->data.Leaving > TimeToLeave) {
                        TimeToLeave = TmpTwo->data.Leaving;
                    }
                    TmpTwo= TmpTwo->FollowingPerson;
                } while (TmpTwo!= LineOnRight->tail);
            }

            temp->data.Leaving = TimeToLeave + temp->data.TimeToPro;
        }

        // Set the timeInQueue
        temp->data.WaitingTime = (temp->data.Leaving - temp->data.TimeOfArrival) * temp->data.ClassSize;

        // Add the current node to the queue
        AddDataStructToLine(temp, LineOnLeft, LineOnRight);
    }

    // Remove the processed nodes from the queue
    DeleteDataStruct(tail->data.TimeOfArrival, LineOnLeft, LineOnRight);

    // Solve for the last node in the list
    if (LineOnLeft->tail == NULL || LineOnRight->tail == NULL) {
        tail->data.Leaving = tail->data.TimeOfArrival + tail->data.TimeToPro;
    } else {
        // Get the exitTime of the last person in the queue
        // If the current group is going to be in left queue, get the exitTime of the last person in the left queue
        // And vice versa
        long long int TimeToLeave = 0;

        int SizeOfLineOnLeft = 0;
        int SizeOfLineOnRight = 0;

        DataStruct * LineTp = LineOnLeft->tail;
        do {
            SizeOfLineOnLeft += LineTp->data.ClassSize;
            LineTp = LineTp->FollowingPerson;
        } while (LineTp != LineOnLeft->tail);
        LineTp = LineOnRight->tail;
        do {
            SizeOfLineOnRight += LineTp->data.ClassSize;
            LineTp = LineTp->FollowingPerson;
        } while (LineTp != LineOnRight->tail);

        if(SizeOfLineOnLeft <= SizeOfLineOnRight || SizeOfLineOnLeft == SizeOfLineOnRight) {
            DataStruct * TmpTwo= LineOnLeft->tail;
            do {
                if (TmpTwo->data.Leaving > TimeToLeave) {
                    TimeToLeave = TmpTwo->data.Leaving;
                }
                TmpTwo= TmpTwo->FollowingPerson;
            } while (TmpTwo!= LineOnLeft->tail);
        }
        else {
            DataStruct * TmpTwo= LineOnRight->tail;
            do {
                if (TmpTwo->data.Leaving > TimeToLeave) {
                    TimeToLeave = TmpTwo->data.Leaving;
                }
                TmpTwo= TmpTwo->FollowingPerson;
            } while (TmpTwo!= LineOnRight->tail);
        }

        tail->data.Leaving = TimeToLeave + tail->data.TimeToPro;
    }

    // Set the timeInQueue
    tail->data.WaitingTime = (tail->data.Leaving - tail->data.TimeOfArrival) * tail->data.ClassSize;

    // This find the total waiting time
    long long int NextTurnTime = TimeUntilNextTurn(tail);

    printf("%lld\n", NextTurnTime);

    return 0;

}

// line front is removed
void dLine(Line * q, Class data) {
    q->tail = DeleteHead(q->tail, data);
}


void eLine(Line * q, Class data) {
    q->tail = TailAd(q->tail, data);
}

// using malloc to create line dynamically
Line * MakeTheLine() {
    Line * result = (Line *) malloc(sizeof(Line));
    result->tail = NULL; // Null emptys the line
    return result;
}

// linked list functions


DataStruct * DeleteHead(DataStruct * tail, Class data) {

    if (tail == NULL) {
        return NULL;
    }


    if (tail->FollowingPerson == tail) {
        tail->data.TimeOfArrival = 0;
        tail->data.ClassSize = 0;
        tail->data.TimeToPro = 0;
        free(tail);
        //free tail
        return NULL;
         // The list will be empty
    }

    DataStruct * PreviousTail = tail;
    DataStruct * PreviousHead = tail->FollowingPerson;
    DataStruct * newHead = PreviousHead->FollowingPerson;

    // Pointer is modded to followingperson
    PreviousTail->FollowingPerson = newHead;

    // Memory is freed to avoid Memory leaks
    free(PreviousHead);

    // Tail is returned
    return PreviousTail;
}

// Addition of group to the circular linked list in the tail
DataStruct * TailAd(DataStruct * tail, Class data) {
    if (tail == NULL) {

        return DataSt(data);
    }


    // Find the pointer to assign them
    DataStruct * PreviousTail = tail;
    DataStruct * PreviousHead = tail->FollowingPerson;
    DataStruct * NextTail = DataSt(data);

    // Pointer are updated to followingperson and nexttail
    PreviousTail->FollowingPerson = NextTail;
    NextTail->FollowingPerson = PreviousHead;

    // Return the NextTail
    return NextTail;
}

DataStruct * DataSt(Class data) {
    DataStruct * result = (DataStruct *) malloc(sizeof(DataStruct));
    result->data = data;
    result->FollowingPerson = result;
    return result;
}

// Classify the group in increasing order from lowest to high
void classify(Class * array, int ClassSize) {
    int i, j;
    Class temp;
    for (i = 0; i < ClassSize; i++) {
        for (j = i + 1; j < ClassSize; j++) {
            if (array[i].TimeOfArrival > array[j].TimeOfArrival) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}



void AddDataStructToLine(DataStruct * node, Line * LineOnLeft, Line * LineOnRight) {
    // If both the lines are Empty then add to left
    if (LineOnLeft->tail == NULL && LineOnRight->tail == NULL) {
        eLine(LineOnLeft, node->data);
    }


    else if (LineOnLeft->tail == NULL) {
        eLine(LineOnLeft, node->data);
    }

    else if (LineOnRight->tail == NULL) {
        eLine(LineOnRight, node->data);
    }

    // go to line with less people
    else {


        // Find the total number of people for left line and right line

        int SizeOfLineOnLeft = 0;
        int SizeOfLineOnRight = 0;
        DataStruct * temp = LineOnLeft->tail;
        do {
            SizeOfLineOnLeft += temp->data.ClassSize;
            temp = temp->FollowingPerson;
        } while (temp != LineOnLeft->tail);
        temp = LineOnRight->tail;
        do {
            SizeOfLineOnRight += temp->data.ClassSize;
            temp = temp->FollowingPerson;
        } while (temp != LineOnRight->tail);

        // Go to the Line with less number of people
        if (SizeOfLineOnLeft <= SizeOfLineOnRight) {
            eLine(LineOnLeft, node->data);
        }
        else {
            eLine(LineOnRight, node->data);
        }
    }
}

// function created to remove data from left line and right line

void DeleteDataStruct(long long int Present, Line * LineOnLeft, Line * LineOnRight) {

    // Return nothing if Both empty
    if (LineOnLeft->tail == NULL && LineOnRight->tail == NULL) {
        return;
    }


    // left Line is empty remove right


    else if (LineOnLeft->tail == NULL) {
        DataStruct * temp = LineOnRight->tail;
        do {
            if (temp->data.Leaving < Present) {
                dLine(LineOnRight, temp->data);
            }

            if (LineOnRight->tail == NULL) {
                break;
            }

            temp = temp->FollowingPerson;
        } while (temp != LineOnRight->tail);
    }
    else if (LineOnRight->tail == NULL) { //if Right line is empty delete left
        DataStruct * temp = LineOnLeft->tail;
        do {
            if (temp->data.Leaving < Present) {
                dLine(LineOnLeft, temp->data);
            }

            if (LineOnLeft->tail == NULL) {
                break;
            }

            temp = temp->FollowingPerson;
        } while (temp != LineOnLeft->tail);
    }
    //Both lines deleted if they are same
    else {
        DataStruct * temp = LineOnLeft->tail;
        do {
            if (temp->data.Leaving < Present) {
                dLine(LineOnLeft, temp->data);
            }

            if (LineOnLeft->tail == NULL) {
                break;
            }

            temp = temp->FollowingPerson;
        } while (temp != LineOnLeft->tail);
        temp = LineOnRight->tail;
        do {
            if (temp->data.Leaving < Present) {
                dLine(LineOnRight, temp->data);
            }

            if (LineOnRight->tail == NULL) {
                break;
            }

            temp = temp->FollowingPerson;
        } while (temp != LineOnRight->tail);
    }
}

// This function will find next waiting time
long long int TimeUntilNextTurn(DataStruct * tail) {
    long long int NextTurnTime = 0;
    DataStruct * temp = tail;

    do {
        NextTurnTime += temp->data.WaitingTime;
        temp = temp->FollowingPerson;
    } while (temp != tail);

    return NextTurnTime;
}

