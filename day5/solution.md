## A

就是求 总结点数$=n$，不含长度$>m$ 的左链的方案数

$f_{i,j}$ 表示 $i$ 个点，不包含长度为 $j$ 的左链的方案数
$$
f_{i,j}=\sum_{k=0}^{i-1}f_{k,j-1}f_{i-k-1,j}
$$

$$
F_j(x)=\sum_{i\geq 0}f_{i,j}x^i\\
F_j(x)=xF_{j-1}(x)F_j(x)+1\\
F_j(x)(1-xF_{j-1}(x))=1\\
F_j(x)=\frac{1}{1-xF_{j-1}(x)}\\
F_j(x)=\frac{A_j(x)}{B_j(x)}\\
F_j(x)=\frac{x}{1-x\frac{A_{j-1}(x)}{B_{j-1}(x)}}=\frac{B_{j-1}(x)}{B_{j-1}(x)-xA_{j-1}(x)}
$$

$$
F_1(x)=\frac{1}{1}\\
F_2(x)=\frac{x}{1-x}\\
$$



## B

就设 $f_i$ 为 两个人都在第 $i$ 只鸽子左边，先手能获得的最多得分

那么
$$
f_i=|a_i-f_{i+1}|
$$

## C

就是有很多个东西的并





应该还是要 meet-in-the-middle 的



对于每个串，可以搞出

