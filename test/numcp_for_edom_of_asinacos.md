# Numerical computation on out-of-domain in $\text{ArcSin}$ and $\text{ArcCos}$

In most cases, if the actual arguments are out-of-domain of the elementary function, the solution can be computed by a built-in function.  
In inverse trigonometric functions, $\text{ArcSin}$ and $\text{ArcCos}$ have a limited domain. (called a branch).  
We use logarithms and power-roots to calculate this. Logarithms and power-roots also have domains, and imaginary numbers appear when the argument is negative.  

$$ \log(x) = \log(-x)+\imath\pi, \text{when}\  x \lt  0 $$
$$ \sqrt{x} = \imath\sqrt{\left| x \right|}, \text{when}\ x \lt 0 $$

If we make full use of this, we can calculate efficiently.  
Now, let's take a look at the formula. $\text{ArcSin}$ and $\text{ArcCos}$ are  

$$ \sin^{-1}(z)=\imath\log(\sqrt{1 - z^2}+\imath z) $$
$$ \cos^{-1}(z)=\frac{\pi}{2}+\imath\log(\sqrt{1 - z^2}+\imath z) $$

Here, we need a variable that appears as an imaginary part, and $\sqrt{1 - z^2}+\imath z$ is used to calculate it.  
Where, let's define this variable $\sqrt{1 - z^2}+\imath z$ as $w$.  
When a variable that satisfies a logarithmic calculation has a negative argument, its appear the imaginary part as a complex argument of $\pi$.  

Applying this to the equation  

$$ \sin^{-1}(z)=-\imath\log(w) $$
$$ \cos^{-1}(z)=\frac{\pi}{2}+\imath\log(w) $$

we obtain. But, since the complex argument of the imaginary part is to be the real part,  

$$ \mathfrak{Re}(\sin^{-1}(z)) = \frac{\pi}{2}, z \gt 1 $$
$$ \mathfrak{Re}(\sin^{-1}(z)) = -\frac{\pi}{2}, z \lt -1 $$
$$ \mathfrak{Re}(\cos^{-1}(z)) = 0, z \gt 1 $$
$$ \mathfrak{Re}(\cos^{-1}(z)) = \pi, z \lt -1 $$

$\sin^{-1}(z)$ and $\cos^{-1}(z)$ are a parity of odd function. So its satisfies  

$$ \sin^{-1}(-z)+\sin^{-1}(z)\equiv 0, $$
$$ \cos^{-1}(-z)+\cos^{-1}(z)\equiv\pi, $$

By the sign value of solution the variable $w$  

$$ \text{sgn}[\mathfrak{Im}[\sin^{-1}(z)]]=-1, \text{when}\ z \gt 1 $$
$$ \text{sgn}[\mathfrak{Im}[\sin^{-1}(z)]]=1, \text{when}\ z \lt -1 $$
$$ \text{sgn}[\mathfrak{Im}[\cos^{-1}(z)]]=1, \text{when}\ z \gt 1 $$
$$ \text{sgn}[\mathfrak{Im}[\cos^{-1}(z)]]=-1, \text{when}\ z \lt -1 $$
