# **Rule Based Sentiment Analysis Project**

Sentiment Analysis is the process of analyzing the sentiment of the text. One way of doing this is
through the polarity of words whether they are positive or negative. Basically we compare each
word of the text with a corpus or lexicon. A sentiment lexicon is a series of words that are
assigned to their respective polarities i.e. positive, negative, and neutral according to their
semantic meaning. The text is passed through different algorithms to process it and to finally
determine the sentiment of a text.

### **Description**

In this project, we will be taking the Amazon review dataset and we will be applying sentiment
analysis on it to determine for each product in the Kindle Store category, how many reviews
were positive and how many reviews were negative, what were the most used positive and
negative words in each review and assign each product a rating on the basis of positive and
negative reviews.

### **Methodology**

#### **Tokenization**

Tokenization is the process of converting the entire text into a list of words known as tokens.
This is the first step in any NLP process. It divides the entire text into meaningful units.

#### **Stopwords Removal**

Stopwords are defined as words that appear frequently in language. They don’t have any
significant role in text analysis and they hamper the sentiment analysis. For example: the, an, a,
or, and, for etc. So they must be removed from the text to get a clearer picture of the text.

#### **Punctuation Removal**

There are punctuation marks in the sentence that are of no use to us. So we have to remove
them before we analyses the sentiments of the words.


#### **Assigning values to polarised words**

Finally, the text only contains meaningful words that we will compare with the defined corpus of
polarised words and assign it a value depending on the fact that whether the word is positive,
neutral or negative. This is called polarity. At the end if the sum of the polarity of each word is
positive then we conclude that the sentiment is positive else if the sum of polarity is negative
then we conclude that the sentiment is negative and if the sum of polarity of each word is zero
we conclude that the sentiment is neutral.

### **Tools and Dataset used**

We will be using the 5-core subset(1.63GB) and metadata subset(474MB) for the category
“Kindle Store” from Amazon Review Data (2018). Along with this we will use a lexicon of
positive words and a lexicon of negative words.
We will take the two data sets from the Amazon Review Data, that are in .JSON formats, and we
will load them into our project using nlohmann’s JSON for Modern C++ API. We will merge these
datasets into one and use data wrangling techniques to process it into a more structure and
uniform dataset. We will use user defined classes such as nodes and C++ STL data structures
such as maps and lists to process this data even further and perform natural language
processing on the review texts. Then we will analyse the data to figure out if the reviews are
positive or negative and learn other interesting features about this data.

**Citations and References:**

_C++ API:_

[https://github.com/nlohmann/json](https://github.com/nlohmann/json)

JSON for Modern C++ API by Niels Lohmann

_Datasets:_

[https://nijianmo.github.io/amazon/index.html](https://nijianmo.github.io/amazon/index.html)

**Justifying recommendations using distantly-labeled reviews and fined-grained aspects**

Jianmo Ni, Jiacheng Li, Julian McAuley

[_Empirical Methods in Natural Language Processing (EMNLP)_ , 2019](http://cseweb.ucsd.edu/~jmcauley/pdfs/emnlp19a.pdf) 


