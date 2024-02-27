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
### 4.2.1 添加baseline
如果奖励是正的，则策略更新的时候会减少这个动作的概率，如果奖励是负的，则策略更新的时候会增加这个动作的概率。但是在一些游戏中，奖励是始终是非负的。于是$R(\tau)$相当于一个权重，在更新参数的时候，奖励大的轨迹会被更新的更多，奖励小的轨迹会被更新的更少。然后做完归一化，奖励大的动作概率会上升，奖励小的动作概率会下降。
*这样看似没有什么问题*
但是注意到，我们计算奖励的期望实际上是一种估算，所以可能存在某些动作没有被采样到，如图所示：
![](https://datawhalechina.github.io/easy-rl/img/ch4/4.13.png)
图中a动作没有被采样到，由于奖励都是正的，其他被采样到的动作的概率会上升，但是a动作的概率不会上升，这样就会导致a动作的概率下降，但是a不一定是一个坏的动作，所以这样的更新是不合理的。
解决办法：
$$R(\tau^n)\rightarrow R(\tau^n)-b$$
$$b\approx \mathbb{E}[R)(\tau)]$$
### 4.2.2 分配合适的分数
只要在同一个回合里面，在同一场游戏里面，所有的状态-动作对就使用同样的奖励项进行加权。这样显然不公平，因为在同一场游戏里面，也许有些动作是好的，有些动作是不好的。 假设整场游戏的结果是好的， 但并不代表这场游戏里面每一个动作都是好的。若是整场游戏结果不好， 但并不代表游戏里面的每一个动作都是不好的。所以我们希望可以给每一个不同的动作前面都乘上不同的权重。所以对一个回合中所有的状态动作同样的奖励项进行加权是不公平的。  
*我的理解：根据上面的添加了基线的公式，如果我们进行了一次“游戏”，得到了一个奖励，如果奖励较好，那个在执行梯度上升的时候，这个“游戏”中的每一个动作的概率都会上升，但是这个“游戏”中的每一个动作的好坏是不一样的，所以我们希望能够给每一个动作一个不同的权重。*
解决办法：
$$\nabla \bar{R}_\theta \approx \frac{1}{N}\sum_{n=1}^{N}{\sum_{t=1}^{T_n}(\sum_{t'=t}^{T_n}{r_{t'}^n-b})\nabla \log p_\theta(a_t^n|s_t^n)}$$
原来的权重是整个回合的奖励，现在的权重是从当前时刻到回合结束的奖励和，因为之前的奖励对当前时刻的动作的影响已经体现在之前的动作的概率上了，所以不需要再考虑之前的奖励。
改进：*加上折扣因子*，**折扣因子一般设为0.9或者0.99。**
$$\nabla \bar{R}_\theta \approx \frac{1}{N}\sum_{n=1}^{N}{\sum_{t=1}^{T_n}(\sum_{t'=t}^{T_n}{\gamma^{t'-t}r_{t'}^n-b})\nabla \log p_\theta(a_t^n|s_t^n)}$$
**那在这种情况下b应该怎么计算呢？？？？？？**
事实上b通常是一个网络估计出来的，它是一个网络的输出。我们把R−b这一项称为优势函数（advantage function），用$A^\theta(s_t,a_t)$表示优势函数。优势函数的优势是一种相对的好，即相对优势。
**但是实际上我还是不知道b怎么计算**
## 4.3 REINFORCE: Monte-Carlo Policy Gradient
这一节介绍策略梯度中最简单最经典的算法：REINFORCE算法。
![](https://datawhalechina.github.io/easy-rl/img/ch4/4.22.png)
