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