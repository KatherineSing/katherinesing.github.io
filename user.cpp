#include "user.h"
#include "tweet.h"
#include <vector>
#include <algorithm>
#include "msort.h"

using namespace std;
/**
 * Constructor 
 */
User::User(string name, unsigned long long  password)
{
  username_ = name;
  password_ = password;
}

/**
 * Destructor
 */
User::~User()
{
  for (list<Tweet*>::iterator it = tweets_.begin(); it != tweets_.end(); ++it) {
    delete *it;
  }
}

/**
 * Gets the name of the user 
 * 
 * @return name of the user 
 */
string User::name() const
{
  return username_;
} 

unsigned long long  User::password() const
{
  return password_;
}



/**
 * Gets all the followers of this user  
 * 
 * @return Set of Users who follow this user
 */
set<User*> User::followers() const
{
  return followers_;
}

set<string> User::namesImFollowing() const
{
  return followingNames_;
}


/**
 * Gets all the users whom this user follows  
 * 
 * @return Set of Users whom this user follows
 */
set<User*> User::following() const
{
  return following_;
}

/**
 * Gets all the tweets this user has posted
 * 
 * @return List of tweets this user has posted
 */
list<Tweet*> User::tweets() const
{
  return tweets_;
}

/**
 * Adds a follower to this users set of followers
 * 
 * @param u User to add as a follower
 */
void User::addFollower(User* u)
{
  followers_.insert(u);
}

/**
 * Adds another user to the set whom this User follows
 * 
 * @param u User that the user will now follow
 */
void User::addFollowing(User* u)
{
  following_.insert(u); 
  followingNames_.insert(u->name());
}
/**
 * Adds the given tweet as a post from this user
 * 
 * @param t new Tweet posted by this user
 * some parsing happens here for hashtags
 */
void User::addTweet(Tweet* t)
{
  tweets_.push_back(t);
}
/**
 * Produces the list of Tweets that represent this users feed/timeline
 *  It should contain in timestamp order all the tweets from
 *  this user and all the tweets from all the users whom this user follows
 *
 * @return vector of pointers to all the tweets from this user
 *         and those they follow in timestamp order
 */
vector<Tweet*> User::getFeed()
{
  //gets my normal feed (not private mention feed)
  vector<Tweet*> myfeedvec;
  //insert everything to the vec
  //me
  for (list<Tweet*>::iterator it = tweets_.begin(); it != tweets_.end(); ++it)
  {
    myfeedvec.push_back(*it);
  }
  //access everyone else's tweets
  //point to a user I'm following
  for(set<User*>::iterator it = following_.begin(); it != following_.end(); ++it)
  {
    User* aUser = *it;
    list<Tweet*> listTweets = aUser->tweets();
    //iterate through the tweets of the users I'm following
    for(list<Tweet*>::iterator it2 = listTweets.begin(); it2 != listTweets.end(); 
      ++it2)
    {
      Tweet* t1 = *it2;
      if (t1->frontMention() == "-")
      {
        myfeedvec.push_back(t1);
      }
      set<string> namesAUserIsFollowing = aUser->namesImFollowing();
      //if he is also following me -> mutual following
      if( namesAUserIsFollowing.find(username_) != namesAUserIsFollowing.end() )
      {
        if((t1->frontMention() == username_))
        {
          myfeedvec.push_back(t1);
        }
      }

    }
  }
  // sort(myfeedvec.begin(),myfeedvec.end(), TweetComp());
  TweetComp var;
  mergesort(myfeedvec, var);
  return myfeedvec;
}