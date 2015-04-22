#ifndef __ROLE_H__
#define __ROLE_H__

#include <time.h>

/**< common for all roles */
enum ROLE_E {
    //occupation type
    
    //race type
    TT = 0,
};


struct role_c {
    unsigned int level:16;
    unsigned int basic_type:16;

    //basic attribute
    unsigned int strength;
    unsigned int agility;
    unsigned int intelligence;

    //third attribute
    unsigned int critical;
    unsigned int master;
    unsigned int haste;
    unsigned int multi_strike;
};

struct basic_skill {
    char name[64];
    unsigned int isdot:1;
    float ba_coefficient;
};

struct warrior {
    struct role_c comm;
    unsigned int basic_critical;
    struct basic_skill comm_attack;
};

struct warrior* 
warrior_init(int level0, int basic_type0, 
             int strength0, int agility0, int intelligence0,
             int critical0, int master0, int haste0, int multi_strike0);
             

#endif  /**< role.h */
