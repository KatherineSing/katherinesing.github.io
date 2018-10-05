#include "tweet.h"
#include "user.h"

using namespace std;

/**
* Models a tweet and provide comparison and output operators
*/

/**
 * Default constructor 
 */
Tweet::Tweet()
{

}

/**
 * Constructor 
 */
Tweet::Tweet(User* user, const DateTime& time, const std::string& text)
{
  time_ = time;
  text_ = text;
  user_ = user;
}

/**
 * Gets the timestamp of this tweet
 *
 * @return timestamp of the tweet
 */
DateTime const & Tweet::time() const
{
  return time_;
}

/**
 * Gets the actual text of this tweet
 *
 * @return text of the tweet
 */
string const & Tweet::text() const
{
  return text_;
}

string & Tweet::frontMention() 
{
  return frontMention_;
}
/**
 * Returns the hashtagged words without the '#' sign
 *
 */
set<string> Tweet::hashTags() const
{
  return hashtags_;
}

set<string> & Tweet::otherMentions() 
{
  return otherMentions_;
}

/**
 * Return true if this Tweet's timestamp is less-than other's
 *
 * @return result of less-than comparison of tweet's timestamp
 */
bool Tweet::operator<(const Tweet& other) const
{
  if (time_< other.time_) return true;
  else return false;
} 

/**
 * Outputs the tweet to the given ostream in format:
 *   YYYY-MM-DD HH::MM::SS username tweet_text
 *
 * @return the ostream passed in as an argument
 */
ostream& operator<<(ostream& os, const Tweet& t)
{

  os << t.time() << " ";
  os << t.user()->name() << " ";
  os << t.text();
  return os;
}

/* Create any other public or private helper functions you deem 
   necessary */

User* Tweet::user() const
{
  return user_;
}

bool Tweet::operator==( const Tweet& t)
{

  if(user_->name() == t.user()->name()
    && text_ == t.text() )
    {return true;}
  else return false;
  
}