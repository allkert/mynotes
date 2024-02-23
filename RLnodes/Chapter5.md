# 五、 近端策略优化算法
## 5.1 重要性采样
上一节介绍的策略梯度算法是一种同策略算法：
$$\nabla \bar{R}_\theta = \mathbb{E}_{\tau \sim p_\theta(\tau)}[R(\tau)\nabla \log p_\theta(\tau)]$$
这个算法的问题在于，每个回合策略都会发生变化，然后重新采样，所以会花很多时间在采样上。
**所以一个想法是，使用异策略算法，这里介绍的重要性采样就是一种异策略算法。**

有一个函数$f(x)$，x的分布服从$p(x)$，我们想求$f(x)$的期望：如果没有办法对$p$积分，则可以从分布中采样一些数据，代入到$f(x)$中求平均值，从而得到近似的$f(x)$的期望。 
$$\mathbb{E}_{x\sim p(x)}[f(x)] = \int p(x)f(x)dx \approx \frac{1}{N}\sum_{i=1}^N f(x_i)$$ 
但是在异策略中，要学习的策略和与环境交互的策略是不一样的，所以不能直接从$p$中采样数据，而只能从另外一个分布$q$中采样数据。做如下的变换：
$$\begin{aligned}
\int f(x)p(x) dx = \int f(x)\frac{p(x)}{q(x)}q(x)dx
= \mathbb{E}_{x\sim q(x)}[f(x)\frac{p(x)}{q(x)}]
\end{aligned}$$
即
$$\mathbb{E}_{x \sim p}[f(x)]=\mathbb{E}_{x\sim q}[f(x)\frac{p(x)}{q(x)}]$$
这样我们就可以从$q$中采样数据，然后代入到$f(x)\frac{p(x)}{q(x)}$中求平均值，从而得到近似的$f(x)$的期望。这个过程就叫做重要性采样。
**但是注意，$f(x)$和$f(x)\frac{p(x)}{q(x)}$的期望虽然是一样的，但是$f(x)$和$f(x)\frac{p(x)}{q(x)}$的方差是不一样的，并且方程的差距是很大的。**

**利用重要性采样，把同策略算法的策略梯度算法改写成异策略算法：**
$$\nabla \overline{R}_\theta = \mathbb{E}_{\tau \sim p_{\theta ^\prime(\tau)}}[\frac{p_\theta(\tau)}{p_{\theta^\prime}(\tau)}R(\tau)\nabla \log p_\theta(\tau)]$$
这样就可以避免每次都要重新采样的问题了。

实际在做策略梯度的时候，我们并不是给整个轨迹$\tau$一样的分数，而是将每一个状态-动作对分开计算。实际更新梯度的过程可写为:
$$\mathbb{E}_{(s_t,a_t)\sim \pi_\theta}[A^\theta(s_t,a_t)\nabla\log p_\theta(a_t^n|s_t^n)]$$
**其中$A^\theta(s_t,a_t)$是优势函数，是一个相对的好，即相对优势。**
利用重要性采样，这个期望可以近似为：
$$\mathbb{E}_{(s_t,a_t)\sim \pi_\theta^\prime}[\frac{p_\theta(s_t,a_t)}{p_\theta^\prime(s_t,a_t)}A^\theta(s_t,a_t)\nabla\log p_\theta(a_t^n|s_t^n)]$$
*这里为什么说是近似呢，因为实际上式子中应该是$A^{\theta^\prime}(s_t,a_t)$而不是$A^\theta(s_t,a_t)$，但是实际上我们会看到状态往往与采取的动作是没有太大的关系的。比如我们玩不同的雅达利游戏，其实看到的游戏画面都是差不多的，以及概率$p_{\theta^\prime}(s_t)$这个概率比较难计算*
所以在实际上使用重要性采样得时候，去优化得目标函数为：
$$J^{\theta^\prime}(\theta)=\mathbb{E}_{(s_t,a_t)\sim \pi_{\theta^\prime}}[\frac{p_\theta(s_t,a_t)}{p_\theta^\prime(s_t,a_t)}A^\theta(s_t,a_t)]$$

## 5.2 近端策略优化
上一节介绍的重要性采样算法虽然可以避免每次都要重新采样的问题，但是如果$p_\theta(a_t|s_t)$和$p_{\theta ^\prime}(a_t|s_t)$相差太多，会导致重要性采样的结果不会太好，近端策略优化（PPO）算法就是为了解决这个问题。
在训练得时候，应多加一个约束来避免$p_\theta(a_t|s_t)$和$p_{\theta ^\prime}(a_t|s_t)$相差太多，即$\theta$和$\theta^\prime$之间的KL散度。
**PPO算法的目标函数为：**
$$J^{\theta^\prime}_{PPO}(\theta)=J^{\theta^\prime}(\theta)-\beta KL(\theta^\prime,\theta)$$  
**TRPO算法：信任区域策略优化算法，其目标函数为：**
*TRPO直接将KL散度作为约束条件，而不是作为目标函数的一部分。*
$$J^{\theta^\prime}_{TRPO}(\theta)=\mathbb{E}_{(s_t,a_t)\sim \pi_{\theta^\prime}}[\frac{p_\theta(s_t,a_t)}{p_\theta^\prime(s_t,a_t)}A^{\theta^\prime}(s_t,a_t)] \\
s.t. KL(\theta, \theta^\prime)<\delta$$
PPO 与 TRPO 的性能差不多，但 PPO 在实现上比 TRPO 容易得多。

### 5.2.1 近端策略优化惩罚
**这节主要介绍PPO算法的两个变种：PPO-Clip（近端策略优化裁剪）和PPO-Penalty（近端策略优化惩罚）**
#### 近端策略优化惩罚
首先初始化一个策略的参数$\theta^0$，然后在每次迭代中，都会用前一轮训练得到的演员的参数$\theta^k$与环境交互，目标函数与PPO一样：
$$J^{\theta^k}_{PPO}(\theta)=J^{\theta^k}(\theta)-\beta KL(\theta^k,\theta)$$
$$H^{\theta^k}_{PPO}(\theta)\approx \sum_
{(s_t,a_t)}{\frac{p_\theta(a_t|s_t)}{p_{\theta^k}(a_t|s_t)}A^{\theta^k}(s_t,a_t)}$$  

#### 近端策略优化裁剪
计算KL散度复杂，所以PPO-Clip算法直接将KL散度去掉，目标函数为：
$$J_{PPO2}^{\theta^k}(\theta)\approx \sum_{(s_t,a_t)}min(\frac{p_\theta(a_t|s_t)}{p_{\theta^k}(a_t|s_t)}A^{\theta^k}(s_t,a_t),clip(\frac{p_\theta(a_t|s_t)}{p_{\theta^k}(a_t|s_t)},1-\epsilon,1+\epsilon)A^{\theta^k}(s_t,a_t))$$
clip函数的意思是将函数的值限制在一个范围内，即clip(x,a,b)的值为x，但是如果x小于a，则值为a，如果x大于b，则值为b。这样就可以避免$p_\theta(a_t|s_t)$和$p_{\theta^k}(a_t|s_t)$相差太多的问题。