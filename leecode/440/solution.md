<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
	tex2jax: {
	  inlineMath: [ ['$','$'], ["\\(","\\)"] ],
	  processEscapes: true
	}
  });
</script>


<script src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script>

# [Leetcode 440](https://leetcode.cn/problems/k-th-smallest-in-lexicographical-order/)

## 题目
给定一个区间 $[1, n]$ ，将区间内的数字按字母序排序，输出第 $k$ 的整数。例如 $n$ 为100，$k$ 为 20。根据字母序升序数组为[1, 10, 100, 11, 12, 13, 14, 15, 16, 17, 18, 19, 2, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 3, 30, ....]，第 20 小的整数为 26。其中 $1 \le k \le n \le 10^9$ 。

## 最朴素解法
将 $[1, n]$ 区间内的所有元素转化为字符串数组，将对应的字符串数组进行排序后，取第 $k$ 个元素。n 最大值为 10 亿，直接进行排序会超时。

## 模拟搜索
字母序生序的序列规律为：

1. 假设 $x$ 为第 $i$ 小的元素。当 $x\times 10 \le n$ 时，第 $i+1$ 小元素为 $x \times 10$；否则为 $x+1$，其中当 $(x+1) \% 10 = 0$ 时，第 $i+1$ 小元素为 $(x+1) / 10$ 。
2. 为加快执行速度，$x+1$ 可转化为 $x + m$ 其中 $m$，取值可见代码。
3. 当 $n$ 很大，且$k \geq \frac{n}{2}$ 时，可通过逆向查找第 $n+1-k$ 个最大元素，来加快搜索的速度。

## 提交结果
尽管增加了逆向搜索，提交时仍然报超时错误（所以测试用例已通过）。在讨论区大家指出时数学题，可能在给定 n 时，1 和 2 之间元素的个数能够直接算出，从而通过 $o(1)$ 来找出结果。