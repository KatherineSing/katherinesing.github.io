#include "twiteng.h"
#include "tweet.h"
#include <iostream>
#include <fstream>
#include <sstream>
// #include <algorithm>
#include <stack>
#include "msort.h"


using namespace std;

vector<TwitEng::Node*> allNodes;
stack<TwitEng::Node*> seenStack;
set<TwitEng::Node*> inStack_set;


void TwitEng::logout()
{
	if(aUserIsLoggedIn == true)
	{
		aUserIsLoggedIn = false;
		cout << "You have logged out." << endl;
	} 
	else cout << "No one is logged in." << endl;
}

bool TwitEng::login(string name, string pw)
{
	// if (!aUserIsLoggedIn)
	// {
		map<string, User*>::iterator it = allUsers.find(name);
		if (it!=allUsers.end())
		{
			if (calculateHash(pw) == (it->second)->password())
			{
				aUserIsLoggedIn = true;
				loggedInUsername = name;
				cout << "Login successful." << endl;
				return false;
			}
		} 
	// }
	cout << "Invalid username/password." << endl;
	return true;
}


void TwitEng::trending(int n)
{
	vector <TagData> temp;
	// while (!trending_.empty())
	// {
	// 	temp.push_back(trending_.top());
	// 	trending_.pop();

	// }	
	// for(unsigned int i = 0; i < temp.size(); i++)
	// {
	// 	trending_.push(temp[i]);
	// }
	// temp.clear();
	for (int i = 0; i < n; i++)
	{
		
		if (!trending_.empty())
		{
			cout << trending_.top().tag << " : " << trending_.top().num << endl;	
			temp.push_back(trending_.top());
			trending_.pop();

		}		
	}
	for(unsigned int i = 0; i < temp.size(); i++)
	{
		trending_.push(temp[i]);
	}
}

void TwitEng::SCC(string filename)
{
	allNodes.clear();
	inStack_set.clear();

	//create User Nodes and store in a vector
	for(map<string, User*>::iterator it = allUsers.begin(); 
		it != allUsers.end(); ++it)
	{
		Node* temp = new Node;
		temp->user = it->second;
		allNodes.push_back(temp);
	}

	//start at any node in allNodes and push to stack seenStack
	int index = 0;
	//for all nodes, call the function
	for(vector<Node*>::iterator it = allNodes.begin(); it != allNodes.end(); ++it)
	{
		if((*it)->id == -1)
		{
			SCChelper(*it, index);
		}

	}
	//print components
	//set< component 1, 2, 3... set<string usernames> >
	ofstream ofile(filename);
	int count = 1; 
	for(set< set<string> >::iterator it = components.begin(); it!= components.end(); ++it)
	{
		ofile << "Component " << count << endl;
		set<string> temp = *it;
		//cout << temp.size();
		for (set<string>::iterator it1 = temp.begin(); it1!= temp.end(); ++it1)
		{
			// ofile << "hello";
			ofile << *it1 << endl;
		}
		count++;
		ofile << endl;
	}
}

void TwitEng::SCChelper(Node*& node, int& index)
//node is a node in the vector allNodes 
{
	//find a user that the Node User is following
	User* u = node->user;
	node->id = index;
	node->lowlink = index;
	index++;
	seenStack.push(node); //stack
	inStack_set.insert(node); //set
	Node* successor;

	set<User*> tempp = u->following();
	for(set<User*>::iterator it5 = tempp.begin();
	 it5 != tempp.end(); ++it5)
	{	
		//access the node y belongs to
		for(vector<Node*>::iterator it1 = allNodes.begin(); 
			it1 != allNodes.end(); ++it1)
		{
			string tempName = ((*it1)->user)->name();
			if (tempName == (*it5)->name()) 
			{
				//********* NODE FOUND ********/
				//if the index is undefined
				successor = *it1;
				break;
			}
		}

		if ((successor)->id == -1)
		{
			SCChelper(successor, index);
			node->lowlink = min(node->lowlink, successor->lowlink);
			
		}
		else if (inStack_set.find(successor) != inStack_set.end() ) 
		// already on stack
		{
			node->lowlink = min(node->lowlink, successor->id);
		}		
	}

	// If v is a root node, pop the stack and generate an SCC
	if(node->lowlink == node->id)
	{
		set<string> temp;
		do
		{
			successor = seenStack.top();
			seenStack.pop();
			inStack_set.erase(successor);
			temp.insert(successor->user->name() );
		}
		while(successor != node);
		components.insert(temp);
	}
}





TwitEng::TwitEng() : trending_(2)
{

}
TwitEng::~TwitEng()
{

	for(map<string, User*>::iterator it = allUsers.begin(); 
		it != allUsers.end(); ++it)
	{
		delete it->second;
	}

}


/**
* Parses the Twitter database and populates internal structures
* @param filename of the database file
* @return true if there is an error, false if successful
*/
bool TwitEng::parse(char* filename)
{
	/******* THE USERS ************/
	ifstream infile(filename);
	string line, name, garbage;
	int numUsers=0, target;
	getline(infile, line);
	stringstream ss(line);
	ss >> target;
	unsigned long long pw;
	while(numUsers!=target) 
	{
		getline(infile, line);
		stringstream ss(line);
		if(ss >> name)
		{
			if (ss >> pw)
			{
				map<string, User*>::iterator it = allUsers.find(name);
				if (it==allUsers.end())
				{	
					User* user = new User(name, pw);
			  		allUsers.insert(make_pair(name , user));
					numUsers++;
					it = allUsers.find(name);
				}
			}
		}		
	}

	ifstream infile2(filename);
		
	getline(infile2, line);
	numUsers = 0;
	while(numUsers!=target) //until first dt is cin'd
	{
		getline(infile2, line);
		stringstream ss(line);
		if(ss >> name)
		{
			User* focusUser = allUsers.find(name)->second;	
			if(ss >> garbage)
			{
				while(ss>>name)
				{
					focusUser->addFollowing(allUsers.find(name)->second);
				}
				numUsers++;
			}
				
		}
	}
	
	ifstream infile3(filename);	
	getline(infile3, line);
	numUsers = 0;
	while(numUsers!=target)
	{
		getline(infile3, line);
		stringstream ss(line);
		if(ss >> name)
		{
			User* focusUser = allUsers.find(name)->second;	
			if(ss >> garbage)
			{
				while(ss>>name)
				{
					(allUsers.find(name)->second)->addFollower(focusUser);
				}
				numUsers++;
			}
		}
	}
	
	/******* THE TWEETS **********/
	DateTime dt;
	string text, username, lino; //user refers to the one tweeting 
	while (getline(infile3, lino))
	{
		bool onlySpaces = true;
		for (unsigned int i = 0; i < lino.size(); i++)
		{
			if(lino[i]!=' ') onlySpaces = false;
		}
		if (lino.empty()||onlySpaces) 
		{
			continue;
		}
		stringstream ss(lino);
		ss >> std::skipws >> dt;
		if (ss.fail() )
		{
			continue;
		}
		ss >> username;
		getline(ss, text);
		unsigned int j = 0;
		while (isspace(text[j]) && j < text.size() - 1)
		{
			text.erase(0, 1);
		}
		addTweet(username, dt, text);
	}
	return false;
}

/**
* Allocates a tweet from its parts and adds it to internal structures
* @param username of the user who made the tweet
* @param timestamp of the tweet
* @param text is the actual text of the tweet as a single string
*/
void TwitEng::addTweet(const std::string& username, const DateTime& time, const std::string& text)
{
	bool onlySpaces = true;
	for (unsigned int i = 0; i < text.size(); i++)
	{
		if(text[i]!=' ') onlySpaces = false;
	}
	if (text.empty()||onlySpaces) 
	{
		return;
	}

	map<string, User*>::iterator it = allUsers.find(username);
	if (it == allUsers.end()) return;


	User* foundName = it->second;

	Tweet* t = new Tweet(foundName, time, text); //, hashtags
	foundName->addTweet(t);
	allTweets.insert(t);
	string line;
	
	//parse for @'s
	stringstream ss1(text);
	ss1 >> line;
	if (line[0]=='@') //if private mention, only add to the private user's
	{
		line.erase(0,1);
		it = allUsers.find(line);
		if (it != allUsers.end() )
		{
			t->frontMention() = line;
		}

		while (getline(ss1, line, '@') )
		{
			getline(ss1, line, ' ');
			it = allUsers.find(line);
			t->otherMentions().insert(line);
		}
	}
	else
	{
		t->frontMention() = "-";
		while (getline(ss1, line, '@') )
		{
			getline(ss1, line, ' ');
			it = allUsers.find(line);
			t->otherMentions().insert(line);
		}
	}
		
	//parse for hashtags
	stringstream ss(text);
	while (getline(ss, line, '#'))
	{
		string hashtag, tempHashtag;
		ss >> tempHashtag;
		bool onlySpaces = true;
		for (unsigned int i = 0; i < tempHashtag.size(); i++)
		{
			if(tempHashtag[i]!=' ') onlySpaces = false;
		}
		if (tempHashtag.empty()||onlySpaces) 
		{
			continue;
		}
		for (unsigned int i = 0; i < tempHashtag.size(); i++)
		{
			hashtag += (char)tolower(tempHashtag[i]);
		}
	
		
		//if hashword exists, insert the tweet
		//if hashword doesn't exist, create set and create pair
		map<string, set<Tweet*> >::iterator it;
		it = allHashtags.find(hashtag); //locate hashtag key
		if (it != allHashtags.end()) //if hashtag key exists
		{
			TagData old(it->first, it->second.size());				
			(it->second).insert(t);	//add tweet to list
			TagData newVal(it->first, it->second.size()); 
			trending_.decreaseKey(old, newVal);
			
		}
		else //if(hashtag) not found
		{
			set<Tweet*> tweets;
			tweets.insert(t);
			allHashtags.insert(make_pair(hashtag, tweets));
			TagData newVal(hashtag, tweets.size());
			trending_.push(newVal);
		}
		t->hashTags().insert(hashtag);
		//it = allHashtags.find(hashtag);
		//add a new tagdata temp(it->first, it->second.size())
	}	
}

void TwitEng::addTweet(const std::string& text) //const std::string& username,
{
	if(aUserIsLoggedIn)
	{
		bool onlySpaces = true;
		for (unsigned int i = 0; i < text.size(); i++)
		{
			if(text[i]!=' ') onlySpaces = false;
		}
		if (text.empty()||onlySpaces) 
		{
			return;
		}

		DateTime time;
		User* foundName = allUsers.find(loggedInUsername)->second;
		if (foundName != allUsers.end()->second)
		{
			Tweet* t = new Tweet(foundName, time, text); //, hashtags
			foundName->addTweet(t);
			allTweets.insert(t);
			
			// parse for @'s
			string line;
			stringstream ss1(text);
			ss1 >> line;
			map<string, User*>::iterator it;
			if (line[0]=='@') //if private mention, only add to the private user's
			{
				line.erase(0,1);
				it = allUsers.find(line);
				if (it != allUsers.end() )
				{
					t->frontMention() = line;
				}

				while (getline(ss1, line, '@') )
				{
					getline(ss1, line, ' ');
					it = allUsers.find(line);
					t->otherMentions().insert(line);
				}
			}
			else
			{
				t->frontMention() = "-";
				while (getline(ss1, line, '@') )
				{
					getline(ss1, line, ' ');
					it = allUsers.find(line);
					t->otherMentions().insert(line);
				}
			}
			
			//parse for hashtags
			stringstream ss(text);
			while (getline(ss, line, '#'))
			{
				string hashtag, tempHashtag;
				ss >> tempHashtag;
				bool onlySpaces = true;
				for (unsigned int i = 0; i < tempHashtag.size(); i++)
				{
					if(tempHashtag[i]!=' ') onlySpaces = false;
				}
				if (tempHashtag.empty()||onlySpaces) 
				{
					continue;
				}
				for (unsigned int i = 0; i < tempHashtag.size(); i++)
				{
					hashtag += (char)tolower(tempHashtag[i]);
				}
				t->hashTags().insert(hashtag);
				//if hashword exists, insert the tweet
				//if hashword doesn't exist, create set and create pair
				map<string, set<Tweet*> >::iterator it;
				it = allHashtags.find(hashtag); //locate hashtag key
				if (it != allHashtags.end()) //if hashtag key exists
				{
					TagData old(it->first, it->second.size());				
					(it->second).insert(t);	//add tweet to list
					TagData newVal(it->first, it->second.size()); 
					//^check if different by 1 from tagdata old
					trending_.decreaseKey(old, newVal);
				}
				else //if(hashtag) not found
				{
					set<Tweet*> tweets;
					tweets.insert(t);
					allHashtags.insert(make_pair(hashtag, tweets));
					TagData newVal(hashtag, tweets.size());
					trending_.push(newVal);

				}			
			}
		}
	}
	else cout << "No user is logged in." << endl;
	
}

void TwitEng::addFollower(string name_to_follow) //string name_of_follower,
{
	if(aUserIsLoggedIn)
	{
		map<string, User*>::iterator it1 = allUsers.find(loggedInUsername);
		map<string, User*>::iterator it2 = allUsers.find(name_to_follow);
		if (it1 != allUsers.end() && it2 != allUsers.end() ) 
		{
			User* follower = it1->second;
			User* toFollow = it2->second; 
			follower->addFollowing(toFollow);
			toFollow->addFollower(follower);
		}
	}
	else cout << "No user is logged in." << endl;
}

/**
* Searches for tweets with the given words and strategy
* @param words is the hashtag terms in any case without the '#'
* @param strategy 0=AND, 1=OR
* @return the tweets that match the search
*/
std::vector<Tweet*> TwitEng::search(std::vector<std::string>& terms, int strategy)
{
	set<Tweet*> current;
	vector<Tweet*> toReturn;
	if(strategy ==0) //AND intersection
	{
		int count = 0;
		for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
		{
			string tempTerm = *it;
			string term;
			for (unsigned int i = 0; i < tempTerm.size(); i++)
			{
				term += (char)tolower(tempTerm[i]);
			}

			if (count == 0)
			{
				//find if the hashtag searched exists
				map<string, set<Tweet*> >::iterator it2 = allHashtags.find(term);
				if(it2 != allHashtags.end())
				{
					current = it2->second;					
					count = 1;
				}
				else return toReturn; //the hashtag does not exist, thus no tweets in its set
			}

			else //count is 1, start removing terms
			{ 
				map<string, set<Tweet*> >::iterator it2 = allHashtags.find(term);
				if (it2!=allHashtags.end() )
				{
					set<Tweet*> other = it2->second; 
					set<Tweet*> temp;
					//find Intersection
					for(set<Tweet*>::iterator it3 = current.begin(); it3 != current.end(); ++it3)
					{
						if ( other.find(*it3) != other.end()) //they do have it in common
						{
							cout << "intersection found" << endl;
							temp.insert(*it3);
						}
					}
					current = temp;
				}
				else return toReturn; //the hashtag does not exist, thus no tweets in its set
			}
		}
		for(set<Tweet*>::iterator it = current.begin(); it!=current.end(); ++it)
		{
			//fill toReturn with current
			toReturn.push_back(*it);
		}
		return toReturn;
	}

	else if(strategy ==1) //OR union
	{
		for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
		{
			string tempTerm = *it;
			string term;
			for (unsigned int i = 0; i < tempTerm.size(); i++)
			{
				term += (char)tolower(tempTerm[i]);
			}
			map<string, set<Tweet*> >::iterator it2 = allHashtags.find(term);
			if (it2 != allHashtags.end())
			{
				set<Tweet*> tweets2 = it2->second;
				for(set<Tweet*>::iterator it3 = tweets2.begin(); it3 != tweets2.end(); ++it3)
				{
					current.insert(*it3);
				}
			}
		}
		for(set<Tweet*>::iterator it3 = current.begin(); it3 != current.end(); ++it3)
		{
			toReturn.push_back(*it3);
		}
		return toReturn;
	}
	return toReturn;
}

/**
* Dump feeds of each user to their own file
*/
void TwitEng::dumpFeeds()
{
	for(map<string, User*>::iterator it = allUsers.begin(); 
		it != allUsers.end(); ++it)
	{
		User* me = it->second;
		/************** FEED FILES *********************/
		vector<Tweet*> myFeed = me->getFeed();

		string tempName = it->first;
		string filename = tempName + ".feed";
		ofstream ofile(filename);
		
		//iterate through to ofile all the tweets
		ofile << me->name() << endl;
		for (vector<Tweet*>::iterator it1 = myFeed.begin(); it1 != myFeed.end(); ++it1)
		{
			ofile << **it1 << endl;
		}

		/************** MENTIONS FILES *********************/
		vector<Tweet*> myfeedvec;
		filename = tempName + ".mentions";
		ofstream ofile1(filename);
		for(map<string, User*>::iterator it1 = allUsers.begin(); 
		it1 != allUsers.end(); ++it1)
		{
			User* him = it1->second;
			if (him != me)
			{
				list<Tweet*> tweets = him->tweets();
				for(list<Tweet*>::iterator it2 = tweets.begin();
				it2 != tweets.end(); ++it2)
				{
					Tweet* t = *it2;
					if (t->frontMention() == me->name()) 
					{
						myfeedvec.push_back(t);
					}

					else if (t->frontMention() == "-" && 
					t->otherMentions().find(me->name()) 
					!= t->otherMentions().end() )
					{
						myfeedvec.push_back(t);
					}

				}
			}
		}
		// sort(myfeedvec.begin(),myfeedvec.end(), TweetComp());
		TweetComp var;
		mergesort(myfeedvec, var);

		ofile1 << me->name() << endl;
		for(vector<Tweet*>::iterator it1 = myfeedvec.begin(); 
			it1 != myfeedvec.end(); ++it1)
		{
			ofile1 << **it1 << endl;
		}

	}	
}

void TwitEng::save(string filename)
{
	ofstream ofile(filename);
	ofile << allUsers.size() << endl;
	for(map<string, User*>::iterator it = allUsers.begin(); 
		it != allUsers.end(); ++it)
	{
		ofile << it->first << " ";
		ofile << it->second->password();
		User* tempUser = it->second;
		set<User*> setFollowing = tempUser->following();
		if (setFollowing.size()!=0)
		{

			for(set<User*>::iterator it1 = setFollowing.begin();
				it1 != setFollowing.end(); ++it1)
			{
				User* temp = *it1;
				ofile << " " << temp->name();
			}
			ofile << endl;
		}
	}
	for(set<Tweet*>::iterator it = allTweets.begin(); it != allTweets.end(); ++it)
	{
		ofile << **it << endl;
	}
}

