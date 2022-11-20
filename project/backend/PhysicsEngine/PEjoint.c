//조인트 선언 부터


struct joint
{
    
    float x[2];
    float v[2];
    float a[2];

    float th;
    float w;
    float alp;

    float F[2];

    float inv_mass;
    float lnv_inertia;

    float delw;
    float delv[2];


};
typedef struct joint Joint;


void prestep(float inv_dt)
{
    //회전하는 값에 대한 내용
}

void applyimpulse()
{
    //Sequential Impulse 회전 버전 내용 추가
}