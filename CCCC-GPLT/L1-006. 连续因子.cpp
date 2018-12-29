L1-006. 连续因子
一个正整数N的因子中可能存在若干连续的数字。例如630可以分解为3*5*6*7，其中5、6、7就是3个连续的数字。给定任一正整数N，要求编写程序求出最长连续因子的个数，并输出最小的连续因子序列。

输入格式：

输入在一行中给出一个正整数N（1<N<231）。

输出格式：

首先在第1行输出最长连续因子的个数；然后在第2行中按“因子1*因子2*……*因子k”的格式输出最小的连续因子序列，其中因子按递增顺序输出，1不算在内。

输入样例：
630
输出样例：
3
5*6*7


分析：用暴力破解，一个个地尝试呀~既然是递增连续的因子长度~那么肯定是不重复的几个连着的数字相乘咯~然后就想到了阶乘的概念对不对~~首先题目说了n最大就2的31次方，后来我掐指一算就知道了2的31次方是介于12的阶乘和13的阶乘之间的大小的~也就是说~~所求连续因子的长度再怎么长~也长不过12个数字~那就从len=12开始，一直到len=1，看看能不能找到一个满足条件的序列咯~
假如长度比1大~那么至少得两个相邻的数相乘~那么这两个数的乘积是不可能超过n的~【就是说如果不止一个因子相乘，那么所求因子序列的第一个数字不可能超过sqrt(n)】那就从start = 2开始（和从1开始相乘是一个意思啦= =乘不乘以1不都一样嘛= =）一直到start = sqrt(n)，把start * (start+ 1)*(start+2)*…【嗯对一共要乘以len的长度个~因为我们现在在尝试是否有连续的len长度的因子相乘满足条件】，乘完了的结果ans看看是不是n的约数~【就是看看n%ans是不是等于0咯】，等于0就好办啦，说明已经找到这个最长的连续因子啦~快输出~~然后直接return~~~耶耶耶~~~要是没找到，那说明什么呢。。说明它是个质数（就是说说明它因子只有他自己本身），那就输出长度为1，而且因子就是n本身咯~~~
你可能会想。。既然len=1为什么要算？因为题目里说输出最小的连续因子序列，那么如果这个数不是质数，也就是说在检验len=1的时候发现了一个比这个数小的因子x，那个这个x就是最小的因子啦，就不能够是等到最后一句输出n为最小的因子啦~~~如果n是质数，那么小于sqrt(n)的限定情况下会保证它不找到n的本身这个数的~~~所以到最后要加上printf(“1\n%d”, n);哦~~~保证它是质数的时候也能被输出答案~~

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    int max = sqrt(n);
    for(int len = 12; len >= 1; len--) {
        for(int start = 2; start <= max; start++) {
            long long int ans = 1;
            for(int i = start; i - start <= len - 1; i++) {
                ans *= i;
            }
            if(n % ans == 0) {
                printf("%d\n%d", len, start);
                for(int i = start + 1; i - start <= len - 1; i++) {
                    printf("*%d", i);
                }
                return 0;
            }
        }
    }
    printf("1\n%d", n);
    return 0;
}

[Update v2.0] 由github用户littlesevenmo提供的更高效的解法
不用算连续因子最多不会超过12个。也不需要三重循环，两重循环即可，直接去计算当前部分乘积能不能整除N，代码如下：

#include <iostream>
#include <cmath>
using namespace std;
long int num, temp;
int main(){
    cin >> num;
    int first = 0, len = 0, maxn = sqrt(num);
    for (int i = 2; i <= maxn; i++){
        int j; temp = 1;
        for (j = i; j <= maxn; j++){
            temp *= j;
            if (num % temp != 0) break;
        }
        if (j - i > len){
            len = j - i;
            first = i;
        }
    }
    if (first == 0) cout << 1 << endl << num;
    else {
        cout << len << endl;
        for (int i = 0; i < len; i++){
            cout << first + i;
            if (i != len - 1) cout << '*';
        }
    }
    return 0;
}