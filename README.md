# My_RegexEngine
<h1>最小化DFA：<h1>
    <h4>我们说一个有穷自动机是化简了的，即是说，它没有多余状态并且它的状态中没有两个是互相等价的。一个有穷自动机可以通过消除多余状态和合并等价状态而转换成一个最小的与之等价的有穷自动机。
    
    所谓有穷自动机的多余状态，是指这样的状态：从该自动机的开始状态出发，任何输入串也不能到达的那个状态。
    
    在有穷自动机中，两个状态s和t等价的条件是：
　	　① 一致性条件 状态s和t必须同时为可接受状态或不可接受状态。
　	　② 蔓延性条件 对于所有输入符号，状态s和状态t必须转换到等价的状态里。<h4>
