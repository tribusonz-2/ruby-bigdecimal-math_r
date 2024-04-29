# bigmath
BigMath module extension for Ruby

標準送付の`bigdecimal`に付属のBigMathモジュールに初等関数を拡張するライブラリです。  
送付の`#log` `#exp`などは定義域・値域・極のエラーのとき例外制御を出しますが、この関数群は例外を投げずInfinityやNaNを送出します。  
