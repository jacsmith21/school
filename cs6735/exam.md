# Exam
## Chap 3
This chapter studies *decision trees*.

### ID3
* Information gain: the amount of information gained by splitting on a certain attribute
* Splits based on information gain
* Only uses categorical data
* Has 2^2^n possible trees where n is the amount of attributes

### Bias & Variance
It is almost always a tradeoff between bias and variance. As # of training samples -> inf. then variance -> 0. Overfitting means high variance whereas underfitting means high bias.

1. How does one integrate high / low variance into any algorithm?
2. How to we handler overfitting for ID3, BN, NN?

#### Restriction Bias
Bias that restricts certain hypotheses such as limiting the size of DTs.

#### Preference Bias
Bias that prefers certain hypotheses

### KFold Cross Validation
Split data into k folds and then train / test on all of them.

### Missing Attributes
* Assign most common value for DT, NB
* Assign most common value of samples with same target for DT, NB
* Assign most common value of samples within some node n for DT
* Omit samples for training for NB, DT
* Omit attributes for NB, DT
* Omit for certain probability calculations for NB
* Use label of the most similar example KNN

### Continuous Attributes
* Discretization DT
* Split by information gain DT
* Give each label it's own input for NN
* Turn categorical data into vector for SVM (similar to NN)
* NB doesn't care
* NB doesn't care either

### Occam's Razor
Prefer shortest algorithms that fits the data.

## Chap 4
This chapter studies *neural networks*.

### Activation Functions
* Perceptron: 1 or -1, is not able to use gradient descent, can only represent linear functions
* Linear: Only able to represent linear functions
* Sigmoid: Continuous and able to represent any function

### Gradient Descent
Using the gradient with respect to the cost function to update the parameters.

### Hidden Layers
* Any continuous function can be represented with two hidden layers but every bounded continuous function can be represented with minimal error with one hidden layer.
* Every Boolean function can be represented with only one hidden layer but may need exponential amount of hidden nodes.

## Chap Ensemble
This chapter studies *ensemble learning*.

### Bagging
This is a technique to reduce variance by assembling strong learners. Only a subset of the data is used for every new learner. Weighted votes are possible.

#### Random Forest
This is just the implementation of bagging on DTs.

### Boosting
This is a technique to reduce bias by assembling weak learners. Weights are used to select certain samples. Therefore, it is prone to overfitting.

## Chap 6
This chapter studies *Bayesian learning*.

### MAP
When choosing a hypothesis, we want the most likely hypothesis given the training data.  
*Maximum a posteriori hypothesis* = hMAP = argmax for h ∈ H of P(h|D) or P(D|h)P(h)/P(D) or P(D|h)P(h)  
If we assume the likelihood of all hypotheses are equal then we can use the maximum likelihood hypothesis hML = argmax for h ∈ H of P(D|h)

### Bayes Optimal Classification
optimal classifer = argmax of v ∈ V for sum of h ∈ H P(v|h)P(h|D)

### Gibbs Classifier
* Choose one hypothesis at random according to P(h|D)
* Error <= 2 x Bayes optimal classifier error

### Naïve Bayes Classifier
* Learn joint distribution over domain using conditional independence
* Useful for text classification
* Useful when large dataset if available
* Use when attributes of sample are independent given classification

```
vMAP  = argmax of v ∈ V for P(v|x)  
      = argmax of v ∈ V for P(x|v)P(v)/P(x)  
      = argmax of v ∈ V for P(x|v)P(v)  
vNP   = argmax of v ∈ V for mult(P(x[i]|v))P(v)  
```

We don't need the probabilities to be correct, we just need the estimations to be the same!

#### Zero Probabilities
Solution -> P*(x[i]|v) = (nc + mp) / (n + m)
* n is # of training samples where v is label
* nc is # of training samples where v is label and x[i] correct is attribute
* p is prior estimate of P*(x[i]|v) usually 1/|v| for uniform distribution
* m is weight given to prior (# of virtual samples) usually |v| for uniform distribution

### Augmented Naïve Bayes
Each attribute will have two parents (another attribute, class) except one which will only be dependent on class. The graph will form a tree. This reduces the bias.

### Bayes Belief Networks (Bayes Nets)
These networks describe conditional independence amongst subsets of variables.

Rules:
- Each node is conditionally independent of it's nondescendants given it's predecessors
- Directed acyclic graph

#### Structure Learning
##### Greedy Search
```
learn(D) {
  create empty network
  until(termination condition met) {
    examine operations -> {
      1. add an arc
      2. delete an arc
      3. change direction of arc
    }
    choose operation to maximize scoring function
  }
}
```
##### Scoring Functions
###### Maximum Log Likelihood
```
P(structure)  = log(P(D|m, θ))
              = sum(log(P(D[i]|m, θ)))
```

###### Cross Validation
See above.

#### Bayesian Information Criterion
Lowest model is preferred. BIC introduces an penalty term for the number of params and arcs.
```
l(m) = -1/2 dm * log(n)
```
* dm is a penalty related to the complexity of m (params / arcs)
* n is the number of samples

#### Minimum Description Length
Prefer the hypothesis that minimizes:
```
hMDL = argmin for h ∈ H of Lc1(h) + Lc2(D|h)
```
where Lc(x) is the description length under encoding C  
For example, L(h) may be # of bits to encode tree h, L(D|h) is # of bits to describe data given h where L(D|h) = 0 if perfectly classified

#### Parameter Learning
We have to learn P(xi|parents(xi)).  

There are several methods we may use for parameter estimation:
* Maximum likelihood parameter estimation
* BIC

### Expectation Maximization
* Observed data X = {x1,...,xn}
* Observed data Z = {z1,...,zn} where zi = {zi1,...,zin} where zij is 1 iff xi generated by jth distribution
* Probability distribution P(Y|h) where Y = {{x1, z1}...{xn, zn}} and h are the parameters
* h = {mu1,...,mun} where n is the amount of distributions
* Determine h that maximizes E[ln(P(Y|h))]

Algorithm:
* Estimation: Q(h'|h) <-E[ln(P(Y|h))]
* Maximization: replace h with h' which maximizes the function Q

Check out this [link](https://www.cs.cmu.edu/~aarti/Class/10601/slides/GrMod3_10_18_2011.pdf).
### Chain Rule
```
P(a1,...,an)  = p(a1|a2,...,an) * p(a2,...,an)  
              = p(a1|a2,...,an) * p(a2|a3,...,an) * p(a3|a4,...,an) ...
```

### Independence
P(A|B) = P(A) then A is absolutely independent of B

#### Conditional Independence
P(X|Y,Z) = P(Z|Z) then X is conditionally independent of Y

### Eager Learning
All algorithms which create a model first before classification.

## Chap XX: Instance Based (Lazy) Learning
### KNN
Distance functions:
* Euclidean distance
* Hammer distance
* Probability based distance

As # of training instances -> infinity then error -> Gibbs classifier error  
As # of training instances & k -> large then error -> Bayes classifier error

### Curse of Dimensionality
* Bad for KNN
* Fine for NB
* Fine for DT

### Local Modals
#### Locally Weighted Regression
Use KNN to find k neighbors then preform regression with distance weighted squared error.
#### Locally Weighted NB Trees
Implement a bays net given the k closest samples.

#### Locally Weighted NB
Implement naïve Bayes given the k closest samples.

## Chap SVM
### LSVM
* Simplest SVM
* Maximize margin
* Linear decision boundary
* Only points that affect the vector affect the output (sorta)
* Use kernel function to augment data to a higher dimension so that data is separable
* Still O(n) even with the kernel function where n is the amount of attributes

### Soft Margin
Minimize cost function (tradeoff between margin and number of misclassified examples)

### Hard Margin
Maximize margin only
