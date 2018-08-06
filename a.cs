using System;
using System.Net;
using System.IO;
using System.Threading;
using System.Collections;
using System.Collections.Generic;

public class Vertex
{
	public Vertex()
	{
		Children = new Hashtable();            
		Leaf = false;
		Parent = -1;
		SuffixLink = -1;
		WordID = -1;
		EndWordLink= -1;
	}

    // Links to the child vertexes in the trie:
    // Key: A single character
    // Value: The ID of vertex
	public Hashtable Children;

    // Flag that some word from the dictionary ends in this vertex
	public bool Leaf;

    // Link to the parent vertex
	public int Parent;

    // Char which moves us from the parent vertex to the current vertex
	public char ParentChar;

    // Suffix link from current vertex (the equivalent of P[i] from the KMP algorithm)
	public int SuffixLink;

    // Link to the leaf vertex of the maximum-length word we can make from the current prefix
	public int EndWordLink;

    // If the vertex is the leaf, we store the ID of the word
	public int WordID;
}

public class Aho
{
	public List<Vertex> Trie;
	List<int> WordsLength;
	public int size = 0;
	int root = 0;

	public Aho()
	{
		Trie = new List<Vertex>();
		WordsLength = new List<int>();
		Init();
	}

	private void Init()
	{
		Trie.Add(new Vertex());            
		size++;
	}

	public void AddString(String s, int wordID)
	{
		int curVertex = root;
		for (int i = 0; i < s.Length; ++i) // Iterating over the string's characters
		{
			char c = s[i];

			// Checking if a vertex with this edge exists in the trie:
			if (!Trie[curVertex].Children.ContainsKey(c))
			{
				Trie.Add(new Vertex());
				
				Trie[size].SuffixLink = -1; // If not - add vertex
				Trie[size].Parent = curVertex;
				Trie[size].ParentChar = c;
				Trie[curVertex].Children[c] = size;
				size++;
			}
			curVertex = (int)Trie[curVertex].Children[c]; // Move to the new vertex in the trie
		}
		// Mark the end of the word and store its ID
		Trie[curVertex].Leaf = true;
		Trie[curVertex].WordID = wordID;
		WordsLength.Add(s.Length);
	}

	public void PrepareAho()
	{
		Queue<int> vertexQueue = new Queue<int>();
		vertexQueue.Enqueue(root);
		while (vertexQueue.Count > 0)
		{
			int curVertex = vertexQueue.Dequeue();
			CalcSuffLink(curVertex);

			foreach (char key in Trie[curVertex].Children.Keys)
			{
				vertexQueue.Enqueue((int)Trie[curVertex].Children[key]);
			}
		}
	}

	public void CalcSuffLink(int vertex)
	{
		// Processing root (empty string)
		if (vertex == root)
		{ 
			Trie[vertex].SuffixLink = root;
			Trie[vertex].EndWordLink = root;
			return;
		}
		// Processing children of the root (one character substrings)
		if (Trie[vertex].Parent == root)
		{ 
			Trie[vertex].SuffixLink = root;
			if (Trie[vertex].Leaf) Trie[vertex].EndWordLink = vertex;
			else Trie[vertex].EndWordLink = Trie[Trie[vertex].SuffixLink].EndWordLink;
			return;
		}
		// Cases above are degenerate cases as for prefix function calculation; the
		// value is always 0 and links to the root vertex.

		// To calculate the suffix link for the current vertex, we need the suffix
		// link for the parent of the vertex and the character that moved us to the
		// current vertex.
		int curBetterVertex = Trie[Trie[vertex].Parent].SuffixLink;
		char chVertex = Trie[vertex].ParentChar; 
		// From this vertex and its substring we will start to look for the maximum
		// prefix for the current vertex and its substring.
		
		while (true)
		{
			// If there is an edge with the needed char, we update our suffix link
			// and leave the cycle
			if (Trie[curBetterVertex].Children.ContainsKey(chVertex))
			{
					Trie[vertex].SuffixLink = (int)Trie[curBetterVertex].Children[chVertex];
					break;
			}
			// Otherwise, we are jumping by suffix links until we reach the root
			// (equivalent of k == 0 in prefix function calculation) or we find a
			// better prefix for the current substring.
			if (curBetterVertex == root)
			{ 
					Trie[vertex].SuffixLink = root;
					break;
			}
			curBetterVertex = Trie[curBetterVertex].SuffixLink; // Go back by sufflink
		}
		// When we complete the calculation of the suffix link for the current
		// vertex, we should update the link to the end of the maximum length word
		// that can be produced from the current substring.
		if (Trie[vertex].Leaf) Trie[vertex].EndWordLink = vertex; 
		else Trie[vertex].EndWordLink = Trie[Trie[vertex].SuffixLink].EndWordLink;
	}

	public int ProcessString(String text)
	{
		// Current state value
		int currentState = root;

		// Targeted result value
		int result = 0;

		for (int j = 0; j < text.Length; j++)
		{
			// Calculating new state in the trie
			while (true)
			{
				Console.WriteLine("{0}\n", currentState);
				// If we have the edge, then use it
				if (Trie[currentState].Children.ContainsKey(text[j]))
				{
					currentState = (int)Trie[currentState].Children[text[j]];
					break;
				}
				// Otherwise, jump by suffix links and try to find the edge with
				// this char

	            // If there aren't any possible edges we will eventually ascend to
	            // the root, and at this point we stop checking.
				if (currentState == root) break;
				currentState = Trie[currentState].SuffixLink;
			}
			int checkState = currentState;

			// Trying to find all possible words from this prefix
			while (true)
			{ 
				Console.WriteLine("{0}", checkState);
				// Checking all words that we can get from the current prefix
				checkState = Trie[checkState].EndWordLink;

				// If we are in the root vertex, there are no more matches
				if (checkState == root) break;
				
				// If the algorithm arrived at this row, it means we have found a
				// pattern match. And we can make additional calculations like find
				// the index of the found match in the text. Or check that the found
				// pattern is a separate word and not just, e.g., a substring.
				result++;
				int indexOfMatch = j + 1 - WordsLength[Trie[checkState].WordID];
		
				// Trying to find all matched patterns of smaller length
				checkState = Trie[checkState].SuffixLink;
			}
		}

		return result;
	}
}

class a{
	static void Main(){
		int n = Convert.ToInt32(Console.ReadLine());
		Aho ac = new Aho();
		for(int i = 0; i < n; ++i){
			string pattern = Console.ReadLine();
			ac.AddString(pattern, i);
		}
		ac.PrepareAho();
		for(int i = 0; i < ac.size; ++i){
			Console.WriteLine("{0} {1}", ac.Trie[i].SuffixLink, ac.Trie[i].EndWordLink);
		}
		string text = Console.ReadLine();
		Console.WriteLine(ac.ProcessString(text));
	}
}