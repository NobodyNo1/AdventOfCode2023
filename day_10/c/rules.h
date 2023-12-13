#ifndef RULES_H
#define RULES_H


#define LEFT    1
#define TOP     2
#define RIGHT   3
#define BOTTOM  4


bool F_connects(int a, int dir) {
    if (dir == LEFT) return false;
    if (dir == TOP) return false;
    if (a=='F') return false;
    return true;
}

bool L_connects(int a, int dir) {
    if (dir == LEFT) return false;
    if (dir == BOTTOM) return false;
    if (a=='L') return false;
    return true;
}

// 7
bool seven_connects(int a, int dir) {
    if (dir == RIGHT) return false;
    if (dir == TOP) return false;
    if (a=='7') return false;
    return true;
}

// 7
bool J_connects(int a, int dir) {
    if (dir == RIGHT) return false;
    if (dir == BOTTOM) return false;
    if (a=='J') return false;
    return true;
}

// -
bool h_connects(int a, int dir) {
    if (a == '|') return false;
    if (dir == TOP) return false;
    if (dir == BOTTOM) return false;
    if (dir == RIGHT){
        if (a == 'F') return false;
        if (a == 'L') return false;
    }
    if (dir == LEFT){
        if (a == '7') return false;
        if (a == 'J') return false;
    }
    return true;
}

// |
bool v_connects(int a, int dir) {
    if (a == '-') return false;
    if (dir == LEFT) return false;
    if (dir == RIGHT) return false;
    if (dir == BOTTOM) {
        if (a == 'F') return false;
        if (a == '7') return false;
    }
    if (dir == TOP){
        if (a == 'L') return false;
        if (a == 'J') return false;
    }
    return true;
}

bool S_connects(int a, int old_dir) {

    int dir = old_dir;
    
    switch (old_dir)
    {
        case TOP: dir = BOTTOM;
        break;
        case BOTTOM: dir = TOP;
        break;
        case LEFT: dir = RIGHT;
        break;
        case RIGHT: dir = LEFT;
        break;
    }

    switch (a)
    {
    case 'S': return S_connects('S', dir);
    case 'F': return F_connects('S', dir);
    case 'L': return L_connects('S', dir);
    case '7': return seven_connects('S', dir);
    case 'J': return J_connects('S', dir);
    case '|': return v_connects('S', dir);
    case '-': return h_connects('S', dir);
    default:
        printf("[ERROR] S: unhandled case!!");
        break;
    }
}

#endif /* RULES_H */
