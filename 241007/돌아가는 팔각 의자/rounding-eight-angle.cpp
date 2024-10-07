#include <iostream>
#include <vector>
using namespace std;

struct Command {
	int n;
	int d;
};

char eight_chairs[5][9];
int k;
vector<Command> commands;
int ans;

void Input();
void Solve();
bool IsEqual(int n, char lr);
void RotateEightChairs(Command cmd);
void RotateEightChair(Command cmd);
int Calc();

int main() {
	Input();
	Solve();

	cout << ans << '\n';

	return 0;
}

void Input() {
	for (int i = 1; i <= 4; i++)
		cin >> eight_chairs[i];

	cin >> k;

	Command cmd;
	for (int i = 0; i < k; i++)
	{
		cin >> cmd.n >> cmd.d;
		commands.push_back(cmd);
	}
}

void Solve() {
	for (int i = 0; i < commands.size(); i++)
		RotateEightChairs(commands[i]);

	ans = Calc();
}

bool IsEqual(int n, char lr) {
	if (lr == 'l') {
		if (eight_chairs[n][6] == eight_chairs[n - 1][2]) return true;
		else return false;
	}
	else {
		if (eight_chairs[n][2] == eight_chairs[n + 1][6]) return true;
		else return false;
	}
}

void RotateEightChairs(Command cmd) {
	vector<Command> cmd_rot;
	cmd_rot.push_back(cmd);

	int tmp_d = cmd.d;
	for (int n = cmd.n; n >= 2; n--)
	{
		if (!IsEqual(n, 'l')) {
			tmp_d *= -1;
			cmd_rot.push_back({ n - 1, tmp_d });
		}
		else break;
	}
	tmp_d = cmd.d;
	for (int n = cmd.n; n <= 3; n++)
	{
		if (!IsEqual(n, 'r')) {
			tmp_d *= -1;
			cmd_rot.push_back({ n + 1, tmp_d });
		}
		else break;
	}

	for (int i = 0; i < cmd_rot.size(); i++)
		RotateEightChair(cmd_rot[i]);
}

void RotateEightChair(Command cmd) {
	if (cmd.d == -1) {
		int tmp = eight_chairs[cmd.n][0];

		for (int i = 1; i < 8; i++)
			eight_chairs[cmd.n][i - 1] = eight_chairs[cmd.n][i];
		
		eight_chairs[cmd.n][7] = tmp;
	}
	else {
		int tmp = eight_chairs[cmd.n][7];

		for (int i = 6; i >= 0; i--)
			eight_chairs[cmd.n][i + 1] = eight_chairs[cmd.n][i];

		eight_chairs[cmd.n][0] = tmp;
	}
}

int Calc() {
	int rst = 0;
	int weight = 1;
	for (int i = 1; i <= 4; i++)
	{
		rst += weight * (eight_chairs[i][0] - '0');
		weight *= 2;
	}
	return rst;
}