import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn import metrics

from sklearn.tree import export_graphviz
from sklearn.externals.six import StringIO  
from IPython.display import Image  
import pydotplus

import os

home = pd.read_csv("domuscpn.csv", header=0)

#Dataset check
home = home.dropna()
print home.head()

#Split dataset in features and target variable

#4 people ID11
#feature_cols = ['event6', 'athome'] #52%

#3 people: brother, mother and father ID14
#feature_cols = ['event6', 'athome'] #63%

#2 people: mother and sister ID12
feature_cols = ['event6', 'athome'] #85%

#2 people: mother and father ID13
#feature_cols = ['event6', 'athome'] #75%

X = home[feature_cols]
y = home.person

# Split dataset into training set and test set
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1)
# 70% training and 30% test

# Create Decision Tree classifer object
clf=RandomForestClassifier(n_estimators=100)

# Train Decision Tree Classifer
clf = clf.fit(X_train,y_train)

#Predict the response for test dataset
y_pred = clf.predict(X_test)

# Model Accuracy, how often is the classifier correct?
print("Accuracy:",metrics.accuracy_score(y_test, y_pred))

#Feature importance
feature_imp = pd.Series(clf.feature_importances_,index=feature_cols).sort_values(ascending=False)
print feature_imp
