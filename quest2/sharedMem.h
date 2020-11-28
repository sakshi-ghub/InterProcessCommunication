#define NOT_READY -1
#define FILLED 0
#define TAKEN 1

struct Memory
{
	int status1;
	int status2;
	int status3;
	char password[10];
	int alphanum;
	int special;
	int strength;
};
