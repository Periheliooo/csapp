# include <stdio.h>
# include <stdlib.h>

void explode_bomb() {
    printf("BOOM!\n");
    exit(1);
}

char *readline() {
    static char buf[100];
    fgets(buf,100,stdin);
    return buf;
}

struct Node {
	int value;
	int index;
	struct Node* next;
};

struct Node nodes[6] = {
    {332, 1, NULL},
    {168, 2, NULL},
    {924, 3, NULL},
    {691, 4, NULL},
    {477, 5, NULL},
    {443, 6, NULL}
};

void init_list() {
    nodes[0].next = &nodes[1];
    nodes[1].next = &nodes[2];
    nodes[2].next = &nodes[3];
    nodes[3].next = &nodes[4];
    nodes[4].next = &nodes[5];
}

struct Node* h = nodes;
struct Node* nodes_p[6];
struct Node** h_p = nodes_p;

void phase_6(char* s) {
	int num[6];
	init_list();
	for (int i = 0; s[i] != '\0' && s[i] != '\n'; i++) {
		num[i] = s[i] - '0';
		if (i >= 6) {
			explode_bomb();
		}
	}

	for (int i = 0; i < 6; i++) {
		if (num[i] <= 0 || num[i] >= 7) {
			explode_bomb();
		}
		for (int j = i + 1; j <= 5; j++) {
			if (num[i] == num[j]) {
				explode_bomb();
			}
		}
	}

	for (int* p = num; p < num + 6; p++) {
		*p = 7 - *p;
	}

	for (int i = 0; i < 6; i++) {
		struct Node* p = h;
		for (int k = 1; k < num[i]; k++) {
			p = p->next;
		}
		*(h_p + i) = p;
	}

	h = h_p[0];
	struct Node* p = h;
	for (int i = 1; i < 6; i++) {
		p->next = h_p[i];
		p = p->next;
	}
	p->next = NULL;

	p = h;
	for (int i = 0; i < 5; i++) {
		if (p->value < p->next->value) {
			explode_bomb();
		}
		p = p->next;
	}

	printf("You defused the bomb!\n");
}

int main() {
	char* input;
	input = readline();
	phase_6(input);
}
