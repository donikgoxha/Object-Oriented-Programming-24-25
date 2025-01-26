#include <iostream>
#include <string>
using namespace std;

class Post {
protected:
    string username;
    string content;
    bool hasPhoto;
    int likes;

public:
    Post() = default;

    Post(const string &username, const string &content, const bool has_photo, const int likes)
        : username(username),
          content(content),
          hasPhoto(has_photo),
          likes(likes) {
    }

    virtual double popularity() const = 0;

    virtual void print() const {
        cout << "Username: " << username << endl;
        cout << "Content: " << content << endl;
        if (hasPhoto) cout << "With photo" << endl;
        else cout << "Without photo" << endl;
        cout << "Likes: " << likes;
    }

    friend bool operator<(const Post &lhs, const Post &rhs) {
        return lhs.popularity() < rhs.popularity();
    }

    friend bool operator<=(const Post &lhs, const Post &rhs) {
        return rhs >= lhs;
    }

    friend bool operator>(const Post &lhs, const Post &rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const Post &lhs, const Post &rhs) {
        return !(lhs < rhs);
    }

    friend double mostPopularPostWithPhoto(Post **posts, int n);
};

class FacebookPost : public Post {
private:
    int shares;

public:
    FacebookPost() = default;

    FacebookPost(const string &username, const string &content, const bool has_photo, const int likes, const int shares)
        : Post(username, content, has_photo, likes),
          shares(shares) {
    }

    double popularity() const override {
        float popularity = likes * shares;
        if (hasPhoto) {
            popularity *= 1.2;
        }
        return popularity;
    }

    void print() const override {
        cout << "Facebook post" << endl;
        Post::print();
        cout << " Shares: " << shares << endl;
        cout << "Popularity: " << popularity() << endl;
    }
};

class TwitterPost : public Post {
private:
    int retweets;
    int replies;

public:
    TwitterPost() = default;

    TwitterPost(const string &username, const string &content, const bool has_photo, const int likes,
                const int retweets, const int replies)
        : Post(username, content, has_photo, likes),
          retweets(retweets),
          replies(replies) {
    }

    double popularity() const override {
        float popularity = likes * retweets * replies;
        if (hasPhoto) {
            popularity *= 1.1;
        }
        if (content.find("#crypto") != -1) {
            popularity *= 1.2;
        }
        return popularity;
    }

    void print() const override {
        cout << "Twitter post" << endl;
        Post::print();
        cout << " Retweets: " << retweets << " Replies: " << replies << endl;
        cout << "Popularity: " << popularity() << endl;
    }
};

double mostPopularPostWithPhoto(Post **posts, int n) {
    double max = -1;
    for (int i = 0; i < n; i++) {
        if (posts[i]->hasPhoto && posts[i]->popularity() > max) {
            max = posts[i]->popularity();
        }
    }
    return max;
}

Post *leastPopularTwitterPost(Post **posts, int n) {
    Post *leastPopular = nullptr;
    for (int i = 0; i < n; i++) {
        if (dynamic_cast<TwitterPost *>(posts[i])) {
            if (leastPopular == nullptr || posts[i]->popularity() < leastPopular->popularity()) {
                leastPopular = posts[i];
            }
        }
    }
    return leastPopular;
}

Post *readFbPost() {
    string username;
    string content;
    bool photo;
    int likes;
    int shares;
    cin.ignore();
    getline(std::cin, username);
    getline(std::cin, content);
    cin >> photo >> likes >> shares;
    return new FacebookPost(username, content, photo, likes, shares);
}

Post *readTwPost() {
    string username;
    string content;
    bool photo;
    int likes;
    int retweets;
    int replies;
    cin.ignore();
    getline(std::cin, username);
    getline(std::cin, content);
    cin >> photo >> likes >> retweets >> replies;
    return new TwitterPost(username, content, photo, likes, retweets, replies);
}

Post **readMultiplePosts(int *n) {
    cin >> *n;
    Post **posts = new Post *[*n];
    for (int i = 0; i < *n; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            posts[i] = readFbPost();
        } else {
            posts[i] = readTwPost();
        }
    }
    return posts;
}

int main() {
    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "Test FacebookPost" << endl;
        Post *post = readFbPost();
        cout << "Popularity: " << post->popularity() << endl;
        post->print();
    } else if (testCase == 2) {
        cout << "Test TwitterPost" << endl;
        Post *post = readTwPost();
        cout << "Popularity: " << post->popularity() << endl;
        post->print();
    } else if (testCase == 3) {
        cout << "Test operator >=" << endl;
        int n;
        Post **posts = readMultiplePosts(&n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if ((*posts[i]) >= (*posts[j])) {
                        cout << i << " >= " << j << endl;
                    } else {
                        cout << i << " < " << j << endl;
                    }
                }
            }
        }
    } else {
        int n;
        Post **posts = readMultiplePosts(&n);
        for (int i = 0; i < n; i++) {
            posts[i]->print();
            cout << endl;
        }
        cout << "The most popular post with photo has a popularity of: " << mostPopularPostWithPhoto(posts, n) << endl;
        cout << "The least popular twitter post is: " << endl;
        Post *result = leastPopularTwitterPost(posts, n);
        if (result == nullptr) {
            cout << "None";
        } else {
            result->print();
        }
    }

    return 0;
}
