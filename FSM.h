#ifndef FSM_H
#define FSM_H

class FSM {
    public:
        typedef void (FSM::*State) (unsigned const sig);
        FSM();
        virtual ~FSM() {};
        void init();
        void dispatch(unsigned const);

    protected:
        void tran(State);
        #define TRAN(target_) tran( static_cast <State>(target_))
        State myState;

    private:
        void initial(unsigned int);
        void idle(unsigned int sig);
};

#endif // FSM_H