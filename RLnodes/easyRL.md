*from:https://datawhalechina.github.io/easy-rl/#/*

# 一. 强化学习基础

## 1.1 概述

*强化学习讨论的是智能体(agent)怎么在复杂的，不确定的环境（environment）中最大化能获得的奖励。RL由智能体和环境两部分组成。在强化学习过程中，智能体与环境一直在交互。智能体在环境中获取某个状态后，它会利用该状态输出一个动作 （action），这个动作也称为决策（decision）。然后这个动作会在环境中被执行，环境会根据智能体采取的动作，输出下一个状态以及当前这个动作带来的奖励。智能体的目的就是尽可能多地从环境中获取奖励。*

![https://datawhalechina.github.io/easy-rl/img/ch1/1.1.png](https://datawhalechina.github.io/easy-rl/img/ch1/1.1.png)



### 1.1.1 RL和supervised learning的区别

**在监督学习中**
1. 输入的数据之间是没有关联的，数据独立同分布。

2. 数据包含labels，告知正确的结果，网络通过正确的标签来变化网络参数，从而修正自己的预测。

**强化学习**：

*在RL中，输入的样本是序列数据，并且与监督学习的数据不同，RL的数据不包含一个正确的label，学习器需要自己去探索尝试，找到奖励最大的动作。因此，智能体获得自己能力的过程，其实是不断地试错探索（trial-and-error exploration）的过程。探索 （exploration）和利用（exploitation）是强化学习里面非常核心的问题。其中，探索指尝试一些新的动作， 这些新的动作有可能会使我们得到更多的奖励，也有可能使我们“一无所有”；利用指采取已知的可以获得最多奖励的动作，重复执行这个动作，因为我们知道这样做可以获得一定的奖励。因此，我们需要在探 索和利用之间进行权衡，这也是在监督学习里面没有的情况。此外，在强化学习过程中，没有非常强的监督者（supervisor），只有**奖励信号（reward signal**），并且奖励信号是延迟的，即环境会在很久以后告诉我们之前我们采取的动作到底是不是有效的。比如玩游戏的过程，只有最后才知道是否成功。*

**强化学习的特点总结**：

3. *探索试错，智能体通过探索环境来获取对环境的理解。*

4. 智能体从环境里获得**延迟的**奖励。

5. 强化学习得到的是有时间关联的数据（sequential data）， 而不是独立同分布的数据。

6. 智能体的动作会影响它随后得到的数据。所以在强化学习里面一个非常重要的问题就是，怎么让智能体的动作一直稳定地提升。

## 1.2 序列决策

智能体的奖励其实是被延迟了的，就是我们现在选取的某一步动作，可能要等到很久后才知道这一步到底产生了什么样的影响。强化学习里面一个重要的课题就是近期奖励和远期奖励的权衡 （trade-off），研究怎么让智能体取得更多的远期奖励。

在与环境的交互过程中，智能体会获得很多观测。针对每一个观测，智能体会采取一个动作，也会得到一个奖励。所以历史是观测、动作、奖励的序列：

$H_t=o_1,a_1,r_1,\ldots,o_t,a_t,r_t$

*状态是对环境的完整描述，观测是对状态的部分描述*

- 在有些情况下智能体的观测不能包含环境运作的所有状态，比如玩纸牌游戏，只能观测到桌面上的纸牌，称环境为**部分可观测的**。这种情况下，强化学习通常被建模为部分可观测马尔可夫决策过程，用一个七元组进行描述$(S,A,T,R,\Omega,O,\gamma)$

## 1.3 动作空间
不同的环境允许不同种类的动作。在给定的环境中,有效动作的集合经常被称为动作空间（action space）。像雅达利游戏和围棋（Go）这样的环境有离散动作空间（discrete action space），在这个动作 空间里，智能体的动作数量是有限的。在其他环境，比如在物理世界中控制一个智能体，在这个环境中就 有连续动作空间（continuous action space）。在连续动作空间中，动作是实值的向量。



## 1.4 RL智能体的组成成分和类型

组成成分：

- 策略(policy)：智能体用策略选取动作。
    1. 随机性策略（stochastic policy）
        输入一个状态s，输出一个概率，这个概率是所有动作的概率，然后通过采样选择智能体采取的动作。
        $$\pi(a|s)=p(a_t=a|s_t=s)$$

    2. 确定性策略（deterministic policy）
    $$a^*=arg max_a\pi(a|s)$$通常情况下，强化学习一般使用随机性策略。  

* 价值函数（value function）：对当前状态进行评估，价值函数越大，说明进入这个状态越有利。

    价值函数里面有一个**折扣因子（discount factor）**，我们希望在尽可能短的时间里面得到尽可能多的奖励。

    $$V_\pi(s)=\mathbb{E}_\pi[G_t|s_t=s]=\mathbb{E}_\pi[\sum_{k=0}^{\infty}{\gamma^kr_{t+k+1|s_t=s}}] \quad  \forall s \in S$$

    Q函数：

    $$Q_{\pi}(s,a)=\mathbb{E}_\pi[G_t|s_t=s,a_t=a]=\mathbb{E}_\pi[\sum_{k=0}^{\infty}{\gamma^kr_{t+k+1}|s_t=s,a_t=a}]$$

- 模型（model）

    模型由状态转移概率和奖励函数两部分组成。

    状态转移概率：

    $$p^{a}_{ss'}=p(s_{t+1}=s'|s_t=s,a_t=a)$$

    奖励：
    $$R(s,a)=\mathbb{E}[r_{t+1}]|s_t=s,a_t=a]$$

* 智能体的分类
  * 分类一
    1. 基于价值的强化学习（value-based reinforcement learning）：智能体显式的学习一个价值函数，然后通过这个价值函数来选择动作。
    2. 基于策略的强化学习（policy-based reinforcement learning）：智能体直接学习一个策略，然后通过这个策略来选择动作。
    3. 将策略和价值结合起来的强化学习（actor-critic reinforcement learning）：智能体同时学习一个策略和一个价值函数，然后通过这个策略和价值函数来选择动作。  
<br/>  
  * 分类二
    根据是否要对环境进行建模，强化学习可以分为两类：
    1. 基于模型的强化学习（model-based reinforcement learning）：智能体学习环境的模型，然后通过这个模型来选择动作。
    ![](https://datawhalechina.github.io/easy-rl/img/ch1/1.35.png)
    2. 免模型的强化学习（model-free reinforcement learning）：智能体不学习环境的模型，直接通过与环境的交互来选择动作。  
<br/>
![](https://datawhalechina.github.io/easy-rl/img/ch1/1.36.png)  
## 1.5 学习和规划
学习（learning）和规划（planning）是序列决策的两个基本问题。
初始时智能体对环境一无所知，它通过不断与环境进行交互，逐渐改进策略。在规划中，环境是已知的，智能体被告知了整个环境的运作规则的详细信息。智能体能够计算出一个完美的模型，并且在不需要与环境进行任何交互的时候进行计算。智能体不需要实时地与环境交互就能知道未来环境，只需要知道当前的状态，就能够开始思考，来寻找最优解。  
## 1.6  探索和利用
探索（exploration）和利用（exploitation）是强化学习里面非常核心的问题。其中，探索指尝试一些新的动作，这些新的动作有可能会使我们得到更多的奖励，也有可能使我们“一无所有”；利用指采取已知的可以获得最多奖励的动作，重复执行这个动作，因为我们知道这样做可以获得一定的奖励。因此，我们需要在探索和利用之间进行权衡，这也是在监督学习里面没有的情况。
  
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

# 第三章 表格型方法
## 3.1 马尔可夫决策过程
马尔可夫决策过程的四元组：$<S,A,P,R>$
下面用熊的例子举例。
### 3.1.1 有模型和无模型
有模型：环境的状态转移概率和奖励函数是已知的。
![](https://datawhalechina.github.io/easy-rl/img/ch3/3.2.png)
无模型：环境的状态转移概率和奖励函数是未知的。
![](https://datawhalechina.github.io/easy-rl/img/ch3/3.3.png)
**二者的区别**
有模型的强化学习算法可以直接使用状态转移概率和奖励函数，而无模型的强化学习算法需要通过与环境的交互来估计状态转移概率和奖励函数。

## 3.2 Q表格
在多次尝试和熊打交道之后，我们就可以对熊的不同的状态做出判断，用状态动作价值来表达在某个状态下某个动作的好坏。下面是Q表格：
![](https://datawhalechina.github.io/easy-rl/img/ch3/3.4.png)
**强化**是指智能体在环境中采取某个动作后，环境会给智能体一个奖励，这个奖励会使智能体的状态动作价值发生变化。

## 3.3 免模型预测
回顾预测的定义：根据马尔可夫决策过程，估计状态的价值函数
在无法获取马尔可夫决策过程的模型情况下，我们可以通过蒙特卡洛方法和时序差分方法来估计某个给定策略的价值。
### 3.3.1 蒙特卡洛策略评估
1. 蒙特卡洛方法
**基于采样的方法**：给定策略$\pi$，让智能体和环境交互，得到很多轨迹，每个轨迹对应一个回报：
$$G_t=r_{t+1}+\gamma r_{t+2}+\dots$$
然后对所有的轨迹进行平均，就可以得到某个状态的价值函数：
$$V_\pi(s)=\mathbb{E}_\pi[G_t|s_t=s]$$
蒙特卡洛方法有一定的局限性，它只能用在有终止的马尔可夫决策过程中。  
2. **动态规划**也是常用的估计价值函数的方法。
动态规划方法使用贝尔曼期望备份，通过上一时刻的状态价值函数来更新当前时刻的状态价值函数，直到收敛。
$$V_i(s)\leftarrow\sum_{a\in A}\pi(a\mid s)\left(R(s,a)+\gamma\sum_{s'\in S}P\left(s'\mid s,a\right)V_{i-1}\left(s'\right)\right)$$
动态规划是有模型的方法。与蒙特卡洛方法相比，动态规划方法的优点是它的估计是稳定的，只需要少量的采样就可以得到准确的结果。但是动态规划方法的缺点是它需要环境的所有信息，包括状态转移概率和奖励函数，这些信息在很多情况下是未知的。状态数量很多的时候，计算量会非常大。
### 3.3.2 时序差分
巴甫洛夫的狗的例子。
给狗喂食，狗会分泌唾液。如果不给狗喂食，狗也会分泌唾液。这是因为狗已经学会了，每次听到铃声就会有食物，所以狗会分泌唾液。这个过程就是条件反射。食物可以认为是奖励，铃声可以认为是状态，开始时铃声是中性的，但是经过多次的训练，铃声就会变成有奖励的状态。当铃声这种条件反射巩固之后，再用一种新的刺激，比如闪光灯，每次闪光灯，然后摇铃，狗也会分泌唾液，逐渐形成第二级的条件反射。
**下一个状态的价值会影响当前状态的价值**
个人理解：*在时序差分的迭代过程中，首先会发现有奖励的状态，然后去影响有奖励的状态的前一个状态，然后会影响有奖励的状态的前两个状态，以此类推，直到所有的状态都被影响，最终收敛。*  

时序差分是介于蒙特卡洛方法和动态规划方法之间的一种方法。它是免模型的，不需要转移矩阵和奖励函数。
时序差分方法的目的是对于某个给定的策略$\pi$，在线地算出它的价值函数$V\pi$。最简单的算法是一步时序差分算法（one-step TD algorithm），它的更新公式如下：
$$V(s_t)\leftarrow V(s_t)+\alpha\left[r_{t+1}+\gamma V\left(s^{\prime}\right)-V(s_t)\right]$$
**时序差分目标**：$r_{t+1}+\gamma V(s_{t+1})$，带衰减的未来奖励的总和，由两部分组成：
1. $r_{t+1}$：即时奖励
2. $\gamma V(s_{t+1})$：未来奖励的总和，$\gamma$是折扣因子，$V(s_{t+1})$是下一个状态的价值函数，$\gamma V(s_{t+1})$是下一个状态的价值函数乘以折扣因子，折扣因子的作用是使得未来奖励的总和越来越小，因为未来的奖励越远，我们越不关心，所以折扣因子越小，未来奖励的总和就越小。
时序差分方法和蒙特卡洛方法的比较：
1. 二者都是免模型的价值估计方法，不需要环境的任何信息，只需要与环境进行交互，就可以估计价值函数。
不同点：
1. 时序差分可以在线学习，而蒙特卡洛方法需要等到一个回合结束之后才能更新价值函数。
2. 时序差分可以从不完整的序列中学习，而蒙特卡洛方法只能从完整的序列中学习。
3. 时序差分可以在连续无终止的任务中学习，而蒙特卡洛方法只能在有终止的任务中学习。
4. 时序差分利用了马尔可夫性质，而蒙特卡洛方法没有利用马尔可夫性质。
**蒙特卡洛没有使用自举，动态规划没有使用采样，时序差分方法同时使用了自举和采样。**
![](https://datawhalechina.github.io/easy-rl/img/ch3/comparison_5.png)
## 3.4 免模型控制
**在不知道马尔可夫决策模型的情况下，得到最佳的策略**
回忆策略迭代：
1. 策略评估：根据策略函数，得到状态价值函数
策略评估的方法：蒙特卡洛方法和动态规划方法（迭代）
2. 策略改进
根据状态价值函数求Q函数，然后迭代策略  

对策略迭代进行广义的推广：：**广义策略迭代**  
问题在于：不知道奖励函数和状态转移概率。之前是通过贝尔曼期望方程来求Q函数，现在不知道奖励函数和状态转移概率，所以无法求Q函数。解决办法是用蒙特卡洛方法估计Q函数。
![](https://datawhalechina.github.io/easy-rl/img/ch3/model_free_control_3.png)
使用蒙特卡洛方法替代动态规划方法估计Q函数，然后进行策略更新：
$$\pi(s)=arg\max_{a}Q(s,a)$$
保证策略迭代收敛的假设是回合有探索性开始。探索性开始保证所有的状态和动作都在无限步的执行后能被采样到，这样才能很好地进行估计。算法如下：
![](https://datawhalechina.github.io/easy-rl/img/ch3/model_free_control_4.png)
**保证蒙特卡洛方法有探索性开始的方法**：***$\epsilon$-贪心策略***
$\epsilon$-贪心策略的定义：以$1-\epsilon$的概率选择最优动作，以$\epsilon$的概率随机选择动作。$\epsilon$通常是一个很小的数，比如0.1，并且随着时间的推移，$\epsilon$会逐渐减小。
价值函数是单调的、改进的，证明如下：
$$\begin{aligned}
Q_\pi(s,\pi^\prime(s)) \\
&= \sum_{a\in A}{\pi^\prime(a|s)Q_\pi(s,a)} \\
&= \frac{\epsilon}{|A|}\sum_{a\in A}{Q_\pi(s,a)}+(1-\epsilon)\max_{a\in A}{Q_\pi(s,a)} \\
&\geq \frac{\epsilon}{|A|}\sum_{a\in A}{Q_\pi(s,a)}+(1-\epsilon)\sum_{a\in A}{\frac{\pi(a|s)-\frac{\epsilon}{|A|}}{1-\epsilon}Q_\pi(s,a)} \\
&= \sum_{a\in A}{\pi(a|s)Q_\pi(s,a)} \\
&= V_\pi(s)
\end{aligned}$$
基于$\epsilon$-贪心策略的蒙特卡洛控制算法：
![](https://datawhalechina.github.io/easy-rl/img/ch3/model_free_control_7.png)
*之前提高过蒙特卡洛方法必需是有终止的马尔可夫决策过程，必需要一个完整的回合才能更新，如果使用时序差分方法，就可以不需要完整的回合，可以在线更新。*
### 3.4.1 Sarsa算法：同策略时序差分控制
利用时序差分方法来估计Q函数
$$Q(s_t,a_t)\leftarrow Q(s_t,a_t)+\alpha\left[r_{t+1}+\gamma Q\left(s_{t+1},a_{t+1}\right)-Q(s_t,a_t)\right]$$
![](https://datawhalechina.github.io/easy-rl/img/ch3/3.14.png)
其中$\alpha$类似于学习率，它的作用是控制更新的幅度，$\alpha$越大，更新的幅度越大，$\alpha$越小，更新的幅度越小。Sarsa属于单步更新算法，每执行一个动作，就会更新一次价值和策略。当然也可以采取n步更新算法，每执行n个动作，就会更新一次价值和策略，得到n步Sarsa算法：
![](https://datawhalechina.github.io/easy-rl/img/ch3/3.15.png)
### 3.4.2 Q学习：异策略时序差分控制
异策略算法：在学习过程中，有两种不同的策略：目标策略(target policy)和行为策略(behavior policy)，目标策略是要学习的策略，行为策略是用来采样的策略。异策略算法的目标是学习目标策略的价值函数，但是采样的策略是行为策略。
在异策略学习的过程中，轨迹都是行为策略与环境交互产生的，但是更新的是目标策略的价值函数。
目标策略：
$$\pi(s_{t+1})=arg\max_{a^\prime}Q(s_{t+1},a^\prime)$$
行为策略采用$\epsilon$-贪心策略，更新公式如下：
$$Q(s_t,a_t)\leftarrow Q(s_t,a_t)+\alpha\left[r_{t+1}+\gamma \max_{a^\prime}Q\left(s_{t+1},a^\prime\right)-Q(s_t,a_t)\right]$$

# 四、策略梯度
## 4.1 策略梯度算法
actor和环境：
![](https://datawhalechina.github.io/easy-rl/img/ch4/4.5.png)
轨迹$\tau=\left(s_{1}, a_{1}, \ldots, s_{T}, a_{T},\right)$
给定actor的参数$\theta$，可以计算某个轨迹发生概率：
$$\begin{aligned}
p_\theta(\tau) &= p(s_1)p_\theta(a_1|s_1)p(s_2|s_1,a_1)p_\theta(a_2|s_2)p(s_3|s_2,a_2)\dots \\
&= p(s_1)\prod_{t=1}^{T}{p_\theta(a_t|s_t)p(s_{t+1}|s_t,a_t)}
\end{aligned}$$
给定某一组参数$\theta$，可以计算奖励的期望：
$$R(\theta)=\sum_{\tau}R(\tau)p_\theta(\tau)=\mathbb{E}_{\tau~p_\theta(\tau)}[R(\tau)]$$
梯度上升法，**不要求奖励函数可微分**：
$$\begin{aligned}
\nabla \bar{R}_\theta&=\sum_\tau{R(\tau)\nabla p_\theta(\tau)} \\
&=\sum_\tau{R(\tau)p_\theta(\tau)\nabla \log p_\theta(\tau)} \\
&=\mathbb{E}_{\tau~p_\theta(\tau)}[R(\tau)\nabla \log p_\theta(\tau)]
\end{aligned}$$
实际上这个期望无法计算，所以我们需要用采样的方法来估计这个期望，即
$$\begin{aligned}\mathbb{E}_{\tau~p_\theta(\tau)}[R(\tau)\nabla \log p_\theta(\tau) &\approx \frac{1}{N}\sum_{n=1}^{N}{R(\tau^{(n)})\nabla \log p_\theta(\tau^{(n)})} \\ &=\frac{1}{N}\sum_{n=1}^{N}{R(\tau^{(n)})\sum_{t=1}^{T}{\nabla \log p_\theta(a_t^{(n)}|s_t^{(n)})}}\end{aligned}$$
参数更新：
$$\theta\leftarrow\theta+\eta \nabla \bar{R}_\theta$$
___
## 4.2 策略梯度实现的技巧

