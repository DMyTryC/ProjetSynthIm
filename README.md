# ProjetSynthIm

How to push to a repository :
-----------------------------
Step 1. Make sure you are working on a branch 
* if you don't work on a branch : 
	* git branch : list current branches
	* git branch "nameBranchLocal" : create a branch with "nameBranchLocal"
	* git checkout "nameBranchLocal" : move to the "nameBranchLocal"

Step 2. Commit changes of your local repository
		
Step 3. Fetch and merge the changes to the current branch
* Commands to execute :
	* git remote -v : list the remote repositories
	* git fetch "nameRemoteRepo" : fetches the files made to the remote repository "name"
	* git merge "nameRemoteRepo"/"nameBranchRemote" "nameBranchLocal" : Merges the files on the "nameRemoteRepo"/"nameBranchRemote" with the "nameBranchLocal" branchs
		
Step 4. Execute maven and clean generated files from pushing
* Commands to execute :
	* mvn install : lets you execute the test life cycle which will test your files for errors
	* bash scriptCleanUp.sh or ./scriptCleanUp.sh : clears the local repository cache from the files that were generated 
	Note : This will not delete them from your local repository, it will just enforce the .gitignore rules
	* Explanation : The files that are written into the .gitignore will still be commited if they are present in the cache of the git repository
				
Step 5. Push the changes to the remote branch
* Recommit if needed
* Push the changes to the remote repository : 
	* git push "nameRemoteRepo" "nameBranchLocal" : This creates a remote repository branch with the same name as the local branch (if it doesn't exist), if it does exist, will push to the remote branch otherwise
