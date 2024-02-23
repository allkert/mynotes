# 二、markov决策过程
## 2.1 markov过程
### 2.1.1 markov性质
$$p\left(X_{t+1}=x_{t+1}\mid X_{0:t}=x_{0:t}\right)=p\left(X_{t+1}=x_{t+1}\mid X_t=x_t\right)$$
### 2.1.2 markov链
离散时间的马尔可夫过程称为马尔可夫过程
$$p\left(s_{t+1}\mid s_{t}\right)=p\left(s_{t+1}\mid h_{t}\right)$$
## 2.2 马尔可夫奖励过程
马尔可夫奖励过程（Markov reward process, MRP）是马尔可夫链加上奖励函数。在马尔可夫奖励过程中，状态转移矩阵和状态都与马尔可夫链一样，只是多了奖励函数（reward function）。
### 2.2.1 回报与价值函数
这里我们进一步定义一些概念。范围(horizon)是指一个回合的长度，它是由有限个步数决定的。回报(return)是指一个回合中所有奖励的总和。我们用$G_t$表示在时刻t的回报，假设时刻t后的奖励序列为$r_{t+1},r_{t+2},\ldots$，那么回报可以表示为：
$$G_t=r_{t+1}+\gamma r_{t+2}+\ldots+\gamma^{T-t-1}r_T$$
其中$\gamma$是折扣因子,越大越重视远期奖励，越小越重视近期奖励。根据回报，我们可以定义状态的价值函数（value function），对于马尔可夫奖励过程，价值函数表示的是从某个状态开始，经过策略$\pi$后，期望获得的回报：
$$\begin{aligned} V^t(s) &=\mathbb{E}_{\pi}\left[G_{t} \mid S_{t}=s\right] \\ &=\mathbb{E}_{\pi}\left[r_{t+1}+\gamma r_{t+2}+\gamma^{2} r_{t+3}+\ldots +\gamma^{T-t-1}r_T \mid S_{t}=s\right] \end{aligned}$$
### 2.2.2 bellman方程
$$V(s)= R(s)+\gamma \sum_{s'\in S}P(s'|s)V(s')$$
bellman方程的证明：
$$\begin{aligned}V(s)&=\mathbb{E}[G_t|s_t=s] \\ 
& = \mathbb{E}[r_{t+1}+\gamma r_{t+2}+\dots|s_t=s] \\
& = \mathbb{E}[r+{t+1}|s_t=s] + \gamma\mathbb{E}[r_{t+2}+\gamma r_{t+3}+\dots|s_t=s] \\
& = R(s)+\gamma\mathbb{E}[G_{t+1}|s_t=s] \\
& = R(s)+\gamma\mathbb{E}[V(s_{t+1})|s_t=s]\\ 
& = R(s) + \gamma \sum _{s^\prime \in S}{p(s^{\prime}|s)V(s^{\prime})}\end{aligned}$$ 
矩阵形式的bellman方程：
$$ V=R+\gamma PV $$
解析解：
$$ V=(I-\gamma P)^{-1}R $$
这个矩阵求逆的复杂度是$O(n^3)$，当状态数很大时，这个计算量是非常大的。因此，我们需要使用迭代的方法来求解。
### 2.2.3 计算markov奖励过程价值的迭代算法
计算方法有：动态规划方法，蒙特卡洛方法，时序差分方法。
#### 蒙特卡洛方法
蒙特卡洛方法是一种基于模拟的方法，它通过采样的方式来估计价值函数。蒙特卡洛方法的优点是不需要环境的任何信息，只需要与环境进行交互，就可以估计价值函数。但是蒙特卡洛方法的缺点是它的估计是不稳定的，需要大量的采样才能得到准确的结果。
![](https://datawhalechina.github.io/easy-rl/img/ch2/2.6.png)
#### 动态规划方法
一直迭代贝尔曼方程，直到价值函数收敛，这种方法称为动态规划方法（dynamic programming, DP）。动态规划方法的优点是它的估计是稳定的，只需要少量的采样就可以得到准确的结果。但是动态规划方法的缺点是它需要环境的所有信息，包括状态转移概率和奖励函数，这些信息在很多情况下是未知的。
![](https://datawhalechina.github.io/easy-rl/img/ch2/2.7.png)
贝尔曼最优方程：
$$V^*(s)=\max_{a\in A}\left(R(s,a)+\gamma \sum_{s'\in S}P(s'|s,a)V^*(s')\right)$$
## 2.3 马尔可夫决策过程
相对于马尔可夫奖励过程，马尔可夫决策过程多了决策（决策是指动作），其他的定义与马尔可夫奖励过程的是类似的。
### 2.3.1Markov决策过程中的策略
$$\pi(a|s)=p(a_t=a|s_t=s)$$
上式表示的是在状态s下，采取动作a的概率。策略定义了在某一个状态应该采取什么样的动作。知道当前状态后，我们可以把当前状态代入策略函数来得到一个概率，即
$$\pi(s)=\left(\pi(a_1|s),\pi(a_2|s),\ldots,\pi(a_n|s)\right)$$
$$\pi(a|s)=p(a_t=a|s_t=s)$$
由此，状态转移为：
$$P_\pi(s\prime|s)=\sum_{a\in A}{\pi(a|s)p(s^\prime|s,a)}$$
解释：在状态s下，采取动作a的概率乘以在状态s下，采取动作a后，转移到状态s'的概率，然后对所有的动作求和，就得到了在状态s下，转移到状态s'的概率。
### 2.3.2 Markov决策过程和Markov奖励过程的关系
![](https://datawhalechina.github.io/easy-rl/img/ch2/2.9.png)  
### 2.3.3 Markov决策过程的价值函数
Markov决策过程中的**价值函数**可以定义为：
$$V_\pi(s) = \mathbb{E}_\pi[G_t|s_t=s]$$
解释：在状态s下，采取策略$\pi$后，期望获得的回报。
**Q函数**也被称为**动作价值函数**：
它的定义：**在状态s下，采取动作a，然后采取策略$\pi$，期望获得的回报。**
$$Q_\pi(s,a)=\mathbb{E}_\pi[G_t|s_t=s,a_t=a]$$
对Q函数中的动作进行加和，就可以得到价值函数：
$$V_\pi(s)=\sum_{a\in A}{\pi(a|s)Q_\pi(s,a)}$$
Q函数的Bellman方程：
$$Q_\pi(s,a)=R(s,a)+\gamma \sum_{s^\prime\in S}{P(s^\prime|s,a)V_\pi(s^\prime)}$$
### 2.3.4 Bellman期望方程
*我们可以把状态价值函数和 Q 函数拆解成两个部分：即时奖励和后续状态的折扣价值（discounted value of successor state）*  通过对状态价值函数进行分解，我们就可以得到一个类似于之前马尔可夫奖励过程的贝尔曼方程————贝尔曼期望方程（Bellman expectation equation）：
$$\begin{aligned} V_{\pi}(s) &=\mathbb{E}_{\pi}\left[G_{t} \mid S_{t}=s\right] \\ &=\mathbb{E}_{\pi}\left[R_{t+1}+\gamma V_{\pi}\left(S_{t+1}\right) \mid S_{t}=s\right] \\ \end{aligned}$$
Q函数也类似：
$$\begin{aligned} Q_{\pi}(s, a) &=\mathbb{E}_{\pi}\left[G_{t} \mid S_{t}=s, A_{t}=a\right] \\ &=\mathbb{E}_{\pi}\left[R_{t+1}+\gamma Q_{\pi}\left(S_{t+1}, A_{t+1}\right) \mid S_{t}=s, A_{t}=a\right] \end{aligned}$$
$$\begin{aligned} 
V_\pi(s) &= \sum_{a\in A}{\pi(a|s)Q_\pi(s,a)}  \\
&= \sum_{a\in A}{\pi(a|s)\left(R(s,a)+\gamma \sum_{s^\prime\in S}{P(s^\prime|s,a)V_\pi(s^\prime)}\right)}
\end{aligned}$$
把这个式子带入Q函数的Bellman方程中，就可以得到：
$$\begin{aligned} Q_{\pi}(s, a) &=R(s, a)+\gamma \sum_{s^{\prime} \in S} P\left(s^{\prime} \mid s, a\right) \sum_{a^{\prime} \in A} \pi\left(a^{\prime} \mid s^{\prime}\right) Q_{\pi}\left(s^{\prime}, a^{\prime}\right) \end{aligned}$$
这个式子可以表示当前时刻的Q函数和未来时刻Q函数的关联。
### 2.3.5 备份图
![](https://datawhalechina.github.io/easy-rl/img/ch2/2.10.png)
备份图也称为回溯图，定义了未来下一时刻状态价值函数和上一时刻的状态价值函数之间的关系。  
Q函数的备份图：
![](https://datawhalechina.github.io/easy-rl/img/ch2/2.12.png)
### 2.3.6 策略评估
策略评估的目的是估计一个策略的价值函数。策略评估的方法有两种：蒙特卡洛方法和动态规划方法。
### 2.3.7 预测与控制
预测（prediction）和控制（control）是马尔可夫决策过程里面的核心问题。预测的输入是Markov决策过程$<S,A,P,R,\gamma>$和策略$\pi$，输出是状态价值函数$V_\pi(s)$或者Q函数$Q_\pi(s,a)$。控制的输入是Markov决策过程$<S,A,P,R,\gamma>$，输出是最优策略$\pi_*$和最优价值函数$V_*(s)$或者$Q_*(s,a)$。
### 2.3.8 Markov决策过程中的策略评估
价值函数迭代：
$$V^{t+1}(s)=\sum_{a\in A}{\pi(a|s)\left(R(s,a)+\gamma \sum_{s^\prime\in S}{p(s^\prime|s,a)V^t(s^\prime)}\right)}$$
**策略评估的核心思想**：反复迭代上式，直到得到一个收敛的价值函数的值
### 2.3.9 Markov决策过程控制
问题：寻找最佳的策略，从而得到最佳价值函数（optimal value function）
最佳价值函数的定义：
$$V_*(s)=\max_{\pi}{V_\pi(s)}$$
最佳策略的定义：
$$\pi_*(s)=\arg\max_{\pi}{V_\pi(s)}$$
当取得最佳价值函数时，可以通过对Q函数进行最大化来得到最佳策略：
$$\pi^*(a|s)=\left\{\begin{array}{ll}{1} & {\text { if } a=\arg \max _{a \in A} Q^{*}(s, a)} \\ {0} & {\text { otherwise }}\end{array}\right.$$
因此，只要知道Q函数，就可以得到最佳策略。Q函数是关于状态与动作的函数，所以如果在某个状态采取某个动作，可以使得 Q 函数最大化，那么这个动作就是最佳的动作。
### 2.3.10 搜索最佳策略
最简单的策略搜索方法是穷举法，它的思想是对所有的策略进行遍历，然后找到最佳的策略。但是这种方法的缺点是它的计算量非常大，因为策略的数量是指数级的。**搜索最佳策略有两种常用的方法：策略迭代和价值迭代。**
#### 策略迭代
策略迭代由两个步骤组成：策略评估和策略改进。策略评估的目的是估计一个策略的价值函数，策略改进的目的是根据策略的价值函数来改进策略。策略迭代的过程是不断地进行策略评估和策略改进，直到策略不再变化，这时候就得到了最佳策略。
策略迭代的图示如下：
![](https://datawhalechina.github.io/easy-rl/img/ch2/2.21.png)
1. 在某种策略下,我们可以得到一个价值函数(策略评估)
2. 根据状态价值函数,利用贝尔曼期望方程，我们可以得到动作价值函数（Q函数）：
$$Q_\pi(s,a)=R(s,a)+\gamma \sum_{s^\prime\in S}{P(s^\prime|s,a)V_\pi(s^\prime)}$$
3. 根据Q函数，得到新一轮的策略：
$$\pi_{i+1}(s)=\arg\max_{a\in A}{Q_{\pi_{i}}(s,a)}$$
**贝尔曼最优方程**：
当停止迭代时，由于选取最佳动作的概率为1，所以状态价值函数就是Q函数：
$$Q_\pi(s,\pi^\prime(s))=\max_{a\in A}Q_\pi(s,a)=Q_*(s,\pi(s))=V_\pi(s)$$
如果已经收敛，则有：
$$V^*(s)=\max_{a\in A}Q^*(s,a)$$
代入到Q函数的贝尔曼期望方程中，化简，就可以得到贝尔曼最优方程：
$$V_*(s)=\max_{a\in A}\left(R(s,a)+\gamma \sum_{s^\prime\in S}{P(s^\prime|s,a)V_*(s^\prime)}\right)$$
#### 价值迭代
**最优性原理**：一个策略 $\pi(a|s)$ 在状态s下是最优的，即$V_\pi(s)=V_*(s)$ 成立，当且仅当对于任何能够从s到达的状态$s^\prime$, 都已经达到了最优价值，即$V_\pi(s^\prime)=V_*(s^\prime)$ 成立。
理解：如果一个策略在某个状态下是最优的，那么这个策略在这个状态下的价值函数就是最优的，如果这个状态可以到达其他状态，那么这些状态的价值函数也是最优的。
**价值迭代的核心思想**：在每一次迭代中，我们都会把当前状态的价值函数更新为下一时刻状态的最大价值函数，直到价值函数收敛。
价值迭代算法：
1. 初始化状态价值函数为0
2. 迭代更新：（k为迭代次数）
$$V_{k+1}(s)\leftarrow\max_{a\in A}\left(R(s,a)+\gamma \sum_{s^\prime\in S}{P(s^\prime|s,a)V_k(s^\prime)}\right)$$
3. 当$V_{k+1}(s)=V_k(s)$时，停止迭代，得到最优价值函数$V_*(s)$根据价值函数提取最优策略