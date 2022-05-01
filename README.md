# **Rule Based Sentiment Analysis Project**
### Read the _Project Report.pdf_ for more details
### **Description**

In this project, we used the Amazon review dataset to conduct a sentiment analysis to determine, for
each product in the Kindle Store category, the number of total reviews, the number of
positive reviews and the number of negative reviews. We also found the top 10 most used
positive and top 10 most used negative words in the reviews of each product and assigned
each product a star rating(out of 5) on the basis of positive reviews and total reviews.

### **Tools and Dataset used**

We used the 5-core subset(1.63GB) and metadata subset(474MB) for the category
“Kindle Store” from Amazon Review Data (2018). Along with this we used a lexicon of
positive words and a lexicon of negative words.
We took the two data sets from the Amazon Review Data, that are in .JSON formats, and we
will load them into our project using nlohmann’s JSON for Modern C++ API. We will merge these
datasets into one and clean the data to process it into a more structured and
uniform dataset. We used multiple C++ STL data structures such as maps,sets and lists to store relevant data and also to process the review texts. We analysed the data to find out if the reviews are positive or negative and learn other interesting features about this data.

**Citations and References:**

_C++ API:_

[JSON for Modern C++ API by Niels Lohmann](https://github.com/nlohmann/json)

_Datasets:_

[https://nijianmo.github.io/amazon/index.html](https://nijianmo.github.io/amazon/index.html)

_Opinion Lexicon:_

Available as 'A list of positive and negative opinion words or
sentiment words for English' from  
http://www.cs.uic.edu/~liub/FBS/sentiment-analysis.html#datasets

Source:
http://www.cs.uic.edu/~liub/FBS/opinion-lexicon-English.rar

Attribution:
"Opinion Lexicon by Bing Liu http://www.cs.uic.edu/~liub is licensed under
CC BY 4.0 International http://creativecommons.org/licenses/by/4.0/"
