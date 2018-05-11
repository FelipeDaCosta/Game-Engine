#ifndef TIME_H
#define TIME_H

class Timer {
    public:
        Timer();
        void Update(float dt);
        void Restart();
        float Get();
    
    private:
        float time;
};

#endif