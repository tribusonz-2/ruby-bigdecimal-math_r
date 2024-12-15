# bigmath
BigMath module extension for Ruby

標準送付の`bigdecimal`に付属のBigMathモジュールに初等関数を拡張するライブラリです。  
送付の`#log` `#exp`などは定義域・値域・極のエラーのとき例外制御を出しますが、この関数群は例外を投げずInfinityやNaNを送出します。  

拡張されるモジュール関数:  
- #log2 (二進対数)
- #log10 (常用対数)
- #cbrt (実数としての三条根)
- #exp2 (二進指数)
- #tan (タンジェント)
- #asin (逆サイン)
- #acos (逆コサイン)
- #sinh (双曲線サイン)
- #cosh (双曲線コサイン)
- #tanh (双曲線タンジェント)
- #asinh (双曲線逆サイン)
- #acosh (双曲線逆コサイン)
- #atanh (双曲線逆タンジェント)
- #hypot (直角三角形の斜辺の長さ)
- #lgamma (ガンマ関数の対数)
