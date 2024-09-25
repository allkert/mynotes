## 演员—评论家算法
演员评论家算法是一种结合**策略梯度**和**时序差分学习**的强化学习方法。借助于价值函数，演员-评论员算法可以进行单步参数更新，不需要等到回合结束才进行更新。
### 策略梯度回顾
$$\nabla \bar{R}_\theta \approx \frac{1}{N}\sum_{n=1}^N\sum_{t=1}^{T_n}{(\sum_{t^\prime=t}^{T_n}{\gamma^{t^\prime-t}r_{t^\prime}^n}-b)\nabla\log p_\theta(a_t^n|s_t^n)}$$  
如果我们把G想成一个随机变量，实际上是在对G做采样，用这些采样的结果去更新参数。但实际上在某一个状态s采取某一个动作a，接下来会发生什么事，其本身是有随机性的。虽然说有一个固定的分布，但其方差可能会非常大。智能体在同一个状态采取同一个动作时，最后得到的结果可能会是很不一样的。当然，假设我们在每次更新参数之前，都可以采样足够多次，那当然就没有以上的问题了。但我们每次做策略梯度，每次更新参数之前都要做一些采样时，采样的次数是不可能太多的。

### 优势演员评论家算法(Advantage Actor-Critic, A2C)
![](https://ai-studio-static-online.cdn.bcebos.com/d02364e1abb64a3db51e2e6cbef2322f4497a4eda56d47a3911a0ba517461800)
A2C算法是一种演员评论家算法，它的演员和评论家是同一个网络。演员网络用来输出动作，评论家网络用来输出状态的价值。
如图，随机变量G的期望是Q值：
$$\mathbb{E}[G_t^n]=Q_{\pi_\theta}(s_t^n,a_t^n)$$
用$Q_{\pi_\theta}(s_t^n,a_t^n)$代替$\sum_{t^\prime=t}^{T_n}{\gamma^{t^\prime-t}r_{t^\prime}^n}$，$V_{\pi_\theta}(s_t^n)$作为基线，就可以把演员与评论员这两个方法结合起来。
如果我们这么实现，有一个缺点，即我们需要估计两个网络：Q网络V网络，但是实际上可以只估计网络V，然后用V表示Q：
$$Q_{\pi_\theta}(s_t^n,a_t^n)=r_t^n+V_\pi(s_{t+1}^n)$$
算法流程：
![](https://ai-studio-static-online.cdn.bcebos.com/a6096d7cce50414ebc574bccf88630900f7afcf0212e4f96bf675b817e7ec252)

### 异步优势演员评论家算法(A3C)
强化学习有一个问题，就是它很慢。因为我们在更新参数的时候，需要不断地与环境交互，然后再更新参数。所以我们可以用多个智能体同时与环境交互，然后再更新参数。这就是A3C算法。
![](https://ai-studio-static-online.cdn.bcebos.com/c36501bcb3ad49c1be3c0486665f6d096e67c00b6d4142a9a00231ae8f299c56)

### 路径衍生策略梯度
![](https://ai-studio-static-online.cdn.bcebos.com/a782c1f5f1204beaa8f1083d25e8fc097d79a15a179d486994827d9b994fa546)
![](https://ai-studio-static-online.cdn.bcebos.com/529577a994a6499698a0e51c2ee470836b5d4d2ffccf4e40b4d760babe331944)