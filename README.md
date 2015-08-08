# Lregex:
            --一个简易的正则表达式引擎
<h2>Building and running</h2>
<h4>Linux, *nix, Mac OSX:<h4>

            $ git clone https://github.com/Leviathan1995/Lregex.git
            $ make
            $ ./Lregex
            
        Ps: windows  vs2013
            如果出现问题错误：stack around the variable “XX” was corrupted.
            把“project->配置属性->c/c++->代码生成->基本运行时检查 设置为默认值，
            就没有这样的错误了。
<h2>Process:</h2>
        Re->NFA->DFA
<h2>Example:</h2>
        Re:a(b|c)a(b|c*)
        字符串：   babaaaabab
        匹配字符串:#aba##abab (#代表匹配失败）
<h2>Algorithm:</h2>
        Re->NFA:
        利用Thompson算法。
        NFA->DFA:
        利用子集构造法。
<h2>Lincense:</h2>

            MIT
