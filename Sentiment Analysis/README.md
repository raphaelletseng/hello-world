Task: train classifiers to distinguish positive and negative sentiments.

Data: The raw text files are stored in rt-polarity.neg for the negative cases, and rt-polarity.pos for the positive
cases.

Research Q: What ML model works well for sentence-level sentiment classification?

** Preprocessing and Feature Extraction **
1. Preprocess input docs to extract feature vector representations of them. Features should be unigram counts. [SciKit-learn's feature word extraction module]

Lemmatize vs Stem vs Stopwords
NLTK: Includes lemmatizers and stemmers and stopword lists for English.

Remove infrequently occurring words as features. [Tune the threshold at which to remove infrequent words]

Experiment with smoothing / regularization in training the models to achieve better results. [SciKit-Learn documentation]

** Setting up the Experiments **
1. Design and implement an experiment that compares model variants to draw reasonable conclusions about which model is the best for generalizing to similar unseen data.

Create subsets of the dataset.

COMPARE:
Logistic Regression
Support Vector Machine (with a linear kernel)
Naive Bayes Algorithm
+ a fourth classification method of choice
+ expected performance of a random baseline (which just guesses positive or negative with equal probability)

each tuned for preprocessing and feature extraction decisions described above.

** Report **
document:
1. Problem setup
2. Experimental procedure
3. Range of parameter settings tried
4. Results and conclusions

Report on performance in terms of accuracy, speculate on success and failures of the models. Which ML learning classifier produced the best performance?
For the best performing model, include a confusion matrix as a form of error analysis.

---

Data split:
training : 80
Testing : 10
Validation : 10
