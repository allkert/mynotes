## DQN
*传统的强化学习使用表格的形式存储状态价值函数和动作价值函数，但是这种方法在状态空间较大时会导致存储空间过大，而且在连续状态空间中无法使用。*
为了在连续得状态和动作空间中计算值函数$Q_\pi(s,a)$,我们可以用一个函数来表示近似计算，称为价值函数近似：
$$Q_\phi(\boldsymbol{s,a})\approx Q_\pi(\boldsymbol{s,a})$$
其中函数$Q_\phi(\boldsymbol{s,a})$是一个参数为$\phi$的函数，用来近似计算$Q_\pi(\boldsymbol{s,a})$。这个函数可以是一个神经网络，也可以是其他的函数。DQN就是一种使用神经网络来近似计算$Q_\pi(\boldsymbol{s,a})$的算法。

### 状态价值函数作为评论员
深度Q网络 是基于价值的算法，在基于价值的算法里面，我们学习的不是策略，而是评论员（critic）。
但是这个评论员不是凭空产生的，它是通过学习得到的。评论员是通过演员（actor）产生的数据来学习的。演员产生的数据是通过和环境交互得到的。所以在基于价值的算法里面，我们需要一个演员和一个评论员。演员产生数据，评论员根据这些数据来学习。
所以在不同的策略之下，状态价值函数也不相同。
评论员通过训练产生，所以它是一个近似的价值函数。那么在训练的时候，则必须有一个目标，这个目标是真实的价值函数。有两种不同的方法来产生这个目标，一种是蒙特卡洛方法，一种是时序差分方法。蒙特卡洛方法是通过一个完整的回合来产生目标，时序差分方法是通过一个步长来产生目标。
#### 蒙特卡洛方法
演员与环境交互，产生很多的数据，这些数据是一个完整的回合。我们可以用这些数据来产生目标。目标是真实的价值函数。我们可以用这个目标来训练评论员。这个方法叫做蒙特卡洛方法。
**此时评论员学习的是回报，即$G_t$**
#### 时序差分方法
$$V_\pi(s_t) = r_t + V_\pi(s_{t+1})$$
在时序差分方法中，并不是直接估计$V_\pi(s_t)$，而是希望$V_\pi(s_t)-V_\pi(s_{t+1})$尽可能的接近$r_t$。

### 动作价值函数作为评论员


### 深度Q网络中的技巧
#### 1.  目标网络（target network）
$$Q_\pi(s_t,a_t) = r_t + Q_\pi(s_{t+1},\pi(s_{t+1}))$$
**如图，$Q_\pi(s_t,a_t)$是网络的输出，$r_t+Q_\pi(s_{t+1},\pi(s_{t+1}))$是目标**
目标是会变动的。当然如果我们要实现这样的训练，其实也没有问题，就是在做反向传播的时候$Q_\pi$的参数会被更新，我们会把两个更新的结果加在一起（因为它们是同一个模型,所以两个更新的结果会加在一起）。但这样会导致训练变得不太稳定。
这里举例猫追老鼠的例子来理解：猫是 Q 估计，老鼠是 Q 目标。一开始，猫离老鼠很远，所以我们想让猫追上老鼠，但是猫和老鼠都在动。猫和老鼠会在优化空间里面到处乱动，这会产生非常奇怪的优化轨迹，使得训练过程十分不稳定。所以我们可以固定 Q 网络，让老鼠动得不那么频繁，可能让它每 5 步动一次，猫则是每一步都在动。如果老鼠每 5 次动一步，猫就有足够的时间来接近老鼠，它们之间的距离会随着优化过程越来越小，最后它们就可以拟合，拟合后就可以得到一个最好的Q 网络。
所以我们会把其中一个 Q 网络，通常是把图右边的 Q 网络固定住。在训练的时候，我们只更新左边的 Q 网络的参数，而右边的 Q 网络的参数会被固定。因为右边的 Q 网络负责产生目标，所以被称为目标网络。   
在实现的时候，我们会把左边的 Q 网络更新多次，再用更新过的 Q 网络替换目标网络。但这两个网络不要一起更新，一起更新，结果会很容易不好。
![](https://datawhalechina.github.io/easy-rl/img/ch6/6.12.png)

#### 2.  探索
使用Q函数来决定动作与使用策略梯度不一样，策略梯度的输出是随机的，它会输出一个动作的分布，我们根据这个动作的分布去采样，所以在策略梯度里面，我们每次采取的动作是不一样的，是有随机性的。像Q函数中，如果我们采取的动作总是固定的，会遇到的问题就是这不是一个好的收集数据的方式。
$$a = \arg\max_aQ_\pi(s,a)$$
这样的问题是，我们会总是采取最大的动作，但是一些没有被探索过的动作可能是更好的。所以我们需要一些探索的方法来解决这个问题。  
##### a. $\epsilon$-贪心策略
它以$\epsilon$的概率随机选择一个动作，以$1-\epsilon$的概率选择一个最优的动作。
$$a = \begin{cases} \arg\max_aQ_\pi(s,a) & \text{with probability } 1-\epsilon \\ \text{random action} & \text{with probability } \epsilon \end{cases}$$
$\epsilon$通常设一个很小的值

##### b. 玻尔兹曼探索
进行类似softmax的操作
假设对于任意的$s, a, Q(s,a)\geq 0$，a被选中的概率与$e^{Q(s,a)/T}$成正比，即：
$$\pi(a|s) = \frac{e^{Q(s,a)/T}}{\sum_{a^\prime \in A}e^{Q(s,a')/T}}$$
其中，T是一个温度参数，T越大，动作被选中的概率越接近均匀分布，T越小，动作被选中的概率越接近贪心策略。   

#### 3.  经验回放
经验回放会构建一个回放缓冲区（replay buffer），回放缓冲区又被称为回放内存（replay memory）。
![](https://datawhalechina.github.io/easy-rl/img/ch6/6.17.png)

### DQN
![](https://datawhalechina.github.io/easy-rl/img/ch6/6.19.png)

