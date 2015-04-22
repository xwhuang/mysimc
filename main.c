#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "role.h"

struct warrior* 
warrior_init(int level0, int basic_type0, 
             int strength0, int agility0, int intelligence0,
             int critical0, int master0, int haste0,  int multi_strike0)
{
    struct warrior *w = malloc(sizeof(struct warrior));
    if (w == NULL) return NULL;
    memset(w, 0, sizeof(struct warrior));

    w->comm.level = level0;
    w->comm.basic_type = basic_type0;

    //basic attribute
    w->comm.strength = strength0;
    w->comm.agility = agility0;
    w->comm.intelligence = intelligence0;

    //third attribute
    w->comm.critical = critical0;
    w->comm.master = master0;
    w->comm.haste = haste0;
    w->comm.multi_strike = multi_strike0;   
///--------------------------------------------------------------------------
    w->basic_critical = 164;

    strcpy(w->comm_attack.name, "COMMON ATTRACK");
    w->comm_attack.isdot = 0;
    w->comm_attack.ba_coefficient = 1.5f;


    return w;
}

static unsigned long 
critical(unsigned int basic, unsigned int critical)
{
    return ((float)critical/(float)basic)*100 > random()%10000?1:0;
}

int
warrior_comm_attack(struct warrior *w)
{
    if (w == NULL) return 0;
    return (w->comm.strength * w->comm_attack.ba_coefficient)* \
        (critical(w->basic_critical, w->comm.critical)?2:1);
}

static void init()
{
    srandom(time(0));
}


int main(int argc, char *argv[])
{
    struct warrior *w;

    init();
    if ((w = warrior_init(100, 0,
                          5000, 100, 100,
                          16300, 1600, 200, 400)) == NULL) {
        perror("warrior init failed!\n");
        exit(1);
    }
    unsigned long sum = 0;
    int i = 0;
#define MAX_ATTACK 1000000    
    while (i++ < MAX_ATTACK) 
        sum += warrior_comm_attack(w);
    printf("      critical : %f\n", (float)w->comm.critical/w->basic_critical);
    printf("comment attack : %lu\n",
           (unsigned long)(w->comm.strength * w->comm_attack.ba_coefficient));
    printf("       average : %lu\n", sum/MAX_ATTACK);
    printf("theory average : %f\n", (((float)w->comm.critical/w->basic_critical)/\
           100 + 1) *
           (unsigned long)(w->comm.strength * w->comm_attack.ba_coefficient));

    return 0;
}
