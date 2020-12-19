import numpy as np
import pandas as pd
import nltk
import string
import random
nltk.download('stopwords')
nltk.download('punkt')
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer
from nltk.stem.porter import PorterStemmer
from nltk.tokenize import word_tokenize
from sklearn import metrics

#Preprocess functions ------------------------
def remove_punctuation(text):
    no_punct = "".join([c for c in text if c not in string.punctuation])
    return no_punct

def remove_stopwords(text):
    words = word_tokenize(text)
    words_without_stopwords = " ".join([w for w in words if w not in stopwords.words('english')])
    return words_without_stopwords

#Lemmatizing
lemmatizer = WordNetLemmatizer()
def word_lemmatizer(text):
    lem_text= "".join([lemmatizer.lemmatize(i) for i in text])
    return lem_text

test = ["the cat, sat on the cat mat and the cat horribly", "hello, it is me."]

def preprocess(sentence):
    t = remove_punctuation(sentence)
    t = remove_stopwords(t)
    t = word_lemmatizer(t)
    return t

def preprocess_array(text_array):
    new_str = []
    for i in text_array:
        new_str.append(preprocess(i))
    return new_str

from sklearn.feature_extraction.text import CountVectorizer
vectorizer=CountVectorizer()
def vectorize(text):
    X = (vectorizer.fit_transform(text))
    return X

#---------------------------------------------
#Organise and preprocess Data

with open('rt-polarity.pos') as f:
    raw_pos = np.loadtxt(f, delimiter="\n", dtype = np.str)#[:30]
sentiment_pos = [1]*5331 #<----- UPDATE AFTER
pos_np = np.array(sentiment_pos)
#print(len(raw_pos))

with open ('rt-polarity.neg') as f:
    #raw_neg = f.readline()
    #raw_neg = [line.rstrip() for line in f]
    raw_neg = np.loadtxt(f, delimiter="\n", dtype =np.str)#[:30]
sentiment_neg = [0]*5331
neg_np = np.array(sentiment_neg)

text_data = np.concatenate((raw_pos, raw_neg))
sentiment_data = np.concatenate((pos_np , neg_np))

preprocess_array(text_data)
print(len(text_data))

X = vectorize(text_data)
X = X.toarray()
print(X.shape)
y = sentiment_data
#print(y.shape)

#--------------------------------------
#Shuffle and create sets
c = list(zip(X, y))
random.shuffle(c)
X, y = zip(*c)

from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, train_size = 0.8, shuffle = True)

#X_valid, X_test, y_valid, y_test = train_test_split(X_test, y_test, test_size=0.5, train_size=0.5)

#---------------------------------------
#Logistic Regression

#np.random.choic(np.arrange(0,1,0.1))
from sklearn.linear_model import LogisticRegression
clf1 = LogisticRegression(random_state = 0, solver = 'lbfgs').fit(X_train, y_train)
clf1.score(X_train, y_train)
clf1_pred = clf1.predict(X_test)
acc_score1 = metrics.accuracy_score(y_test, clf1_pred)
print('Accuracy Classification Score LR: {}'.format(acc_score1))

#---------------------------------------
#Support Vector Machine

from sklearn import svm
clf2 = svm.SVC(kernel='linear', random_state = 0)
clf2.fit(X_train, y_train)
clf2_pred = clf2.predict(X_test)
acc_score2 = metrics.accuracy_score(y_test, clf2_pred)
print('Accuracy Classification Score SVM: {}'.format(acc_score2))
#compare to y_test

#--------------------------------------
# Naive Bayes

from sklearn.naive_bayes import MultinomialNB
clf3 = MultinomialNB().fit(X_train, y_train) #target set
clf3_pred = clf3.predict(X_test)
print(clf3_pred)
acc_score3 = metrics.accuracy_score(y_test, clf3_pred)
print('Accuracy Classification Score Bayes: {}'.format(acc_score3))
#print accuracy of test
print(metrics.confusion_matrix(y_test, clf3_pred))

#---------------------------------------
# Else
from sklearn.linear_model import SGDClassifier
clf4 = SGDClassifier().fit(X_train, y_train) #target set
clf4_pred = clf4.predict(X_test)
acc_score4 = metrics.accuracy_score(y_test, clf4_pred)
#print(clf4_pred.shape)
print('Accuracy Classification Score Linear SVM: {}'.format(acc_score4))

#--------------------------------------
#Baseline Expected performance
#Guesses positive and negative with equal probability
#Bernoulli?

#nums = randi([0,1], (), N)
opts = [0,1]
optsa = np.array(opts)
baseline = np.random.choice(opts, len(X_test))
#print(baseline.shape)
acc_scorebase = metrics.accuracy_score(y_test, baseline)
print('Accuracy Classification Score baseline: {}'.format(acc_scorebase))


#base = np.random.binomial(1, 0.5, len(X_test))


#-------------------------------------
#shuffle two arrays the same ways
#split after
#1 hot encoding -> unique words in dataset_combined
# X needs to be a vector
# create mapping of word to vectors

#100 most common words and one unknown
#remove words which occur ounce


##TF-IDF
#from sklearn.feature_extraction.text import TfidTransformer
#tridf_trans = TfidTransformer()
#def tfidf(text):
#    train_tfidf = tfidf_trans.fit_transform
#cleaned_neg = remove_punctuation(raw_neg)
#cleaned_neg = remove_stopwords(cleaned_neg)
#cleaned_neg = word_lemmatizer(cleaned_neg)
#data_neg = [cleaned_neg]
#arr_data = vectorizer.fit_transform(data_neg)

#counting threshold (1)
#tfidf
