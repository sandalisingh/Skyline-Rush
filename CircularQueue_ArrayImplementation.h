#ifndef CircularQueue_ArrayImplementation_h
#define CircularQueue_ArrayImplementation_h

#include "Car.h"

#include <iostream>
using namespace std;

class CQ{   //Circular Queue of Incoming Cars
        int front , rear , size;
        int Initiate_This_IC;
        Incoming_Car **Q;
        
        bool isEmpty();
        bool isFull();

    public:
        CQ();
        
        void Enqueue(Incoming_Car* x);       
        Incoming_Car* Peek();
        void TraverseToNext();  //

        void Render(SDL_Renderer *renderer);    //to render the IC returns the pointer to next IC in a loop

        void Increement_Y();

        bool CheckCollision(User_Car &C);   //returns TRUE when collided
        bool KeepDistance(User_Car &C); //true: crashes

        
};

CQ :: CQ(){
    cout<<"\nCQ()";
    size = 5;   //NoOfPoliceCars
    front =  -1;
    rear = -1;
    Q = new Incoming_Car* [size];
    for(int i = 0; i < size; i++){
        Q[i] = NULL;
    }
}

void CQ :: Increement_Y(){  
    cout<<"\n\tCQ :: Increement_Y()";
    for(int i = 0; i < size; i++){
        if( (Q[i]->pos.y <= 640) && (Q[i]->pos.y >= - Q[i]->H) ){
            Q[i]->pos.y += Q[i]->moveStep;
        }
    }
}

void CQ :: Enqueue(Incoming_Car *x){
    cout<<"\n\tCQ :: Enque()";

    if(isFull()){
        cout<<"\nOVERFLOW!\n"<<endl;
    }else{
        if(front == -1){
            front = 0;
        }
        rear = (rear + 1) % size;
        Q[rear] = x;
    }
}

inline bool CQ :: isEmpty(){
    return (front == -1);
}

inline bool CQ :: isFull(){
    return ( (rear + 1) % size == front );
}

Incoming_Car* CQ :: Peek(){
    cout<<"\n\tCQ :: Peek()";

    Incoming_Car* IC = NULL;
    IC = Q[Initiate_This_IC];

    return IC;
}

void CQ :: TraverseToNext(){
    cout<<"\n\tCQ :: TraverseToNext()";

    Initiate_This_IC = (Initiate_This_IC + 1) % size;
}

void CQ :: Render(SDL_Renderer *renderer){
    cout<<"\n\tCQ :: Render()";

    for(int i = 0; i < size ; i++){
        Q[i]->Render(renderer);
    }
}

bool CQ :: CheckCollision(User_Car &C){
    cout<<"\n\tCQ :: CheckCollision()";

    for(int i = 0; i < size ; i++){
        if(
                ( Q[i]->pos.y + Q[i]->H  == C.pos.y )
            ||  ( C.pos.y > Q[i]->pos.y  &&  C.pos.y < Q[i]->pos.y + Q[i]->H )
        ){
            if(
                ( ((C.pos.x + C.W ) > (Q[i]->pos.x )) && ((C.pos.x + C.W ) < (Q[i]->pos.x + Q[i]->W)) ) //Left to IC
                || ( (Q[i]->pos.x) == (C.pos.x) )                                                               //head to head
                || ( ((C.pos.x) < (Q[i]->pos.x + Q[i]->W)) && ((C.pos.x ) > (Q[i]->pos.x)) )           //Right to IC
            ){
                return true;
            }
        }
    }
    return false;
}

bool CQ :: KeepDistance(User_Car &C){   //true: crashed
    cout<<"\n\tCQ :: KeepDistance()";

    bool crash = false;

    for(int i = 0; i < size ; i++){
        if( 
           (  ( (C.pos.y) > (Q[i]->pos.y) )   &&  ( (C.pos.y) < (Q[i]->pos.y + Q[i]->H) )  )
           //||  (  ( (C.pos.y + C.H) > (Q[i]->pos.y) )   &&  ( (C.pos.y + C.H) < (Q[i]->pos.y + Q[i]->H) )  )
        ){
            if(     //overlap from the right of the IC
                (  ( (C.pos.x) < (Q[i]->pos.x)  )  &&  ( (C.pos.x) > (Q[i]->pos.x + Q[i]->W) )  ) 
            ){
                C.pos.x = (Q[i]->pos.x + Q[i]->W);
                crash = true;
            }
            
            else if(     //overlap from left of the IC
                (  ( (C.pos.x + C.W) > (Q[i]->pos.x)  )  &&  ( (C.pos.x + C.W) < (Q[i]->pos.x + Q[i]->W) )  ) 
            ){
                C.pos.x = (Q[i]->pos.x - C.W);
                crash = true;
            }
        }
        // else if(
        //     (
        //         (  ( C.pos.x > Q[i]->pos.x ) && ( C.pos.x < Q[i]->pos.x + Q[i]->W )  )
        //         || (  ( C.pos.x + C.W > Q[i]->pos.x ) && ( C.pos.x + C.W < Q[i]->pos.x + Q[i]->W )  )
        //     )
        //     &&
        //     (       //overlap from top of the IC
        //         (  ( (C.pos.y + C.H) > (Q[i]->pos.y)  )  &&  ( (C.pos.y + C.H) < (Q[i]->pos.y + Q[i]->H) )  ) 
        //     )
        // ){
        //     C.pos.y = (Q[i]->pos.y - C.H);
        //     crash = true;
        // }
    }

    return crash;
}

#endif 