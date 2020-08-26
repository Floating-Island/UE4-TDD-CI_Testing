# UE4-TDD-CI_Testing
Project Template to use on TDD and CI with Unreal Engine 4 on Windows.

Requirements:
  -Unreal Engine 4 (4.22).
  -git.
  -github.
  -ngrok.
  -Jenkins.
  -OpencppCodeCoverage.

I assume you understand how Test-Driven Development (TDD) and Continuous Integration (CI) works.

Introduction:

Unreal Engine provides a testing suite inside it's Automation Framework, but it's tedious (and consumes a lot of time) to write a test, build the project, open the editor,
 run the tests and see if they pass or fail.

There's a way to do the tests more efficiently (you still have to create a class from within the editor to use it as a test class so the engine 'sees' it),
 without having to wait to the editor and check the results for yourself.

That's when you need Jenkins, and automation program that triggers a pipeline execution via an event.
A pipeline is a configuration of a workspace environment, a series of stages, each of them consisting of a series of steps, and finally things that you do after (post) the
 pipeline is executed.

Inside that pipeline we're going to declare how to build the project, run our tests, check if they fail or pass and also which parts aren't tested (via code coverage).

How's the process then?

1) you code locally (create tests, classes, etc).
2) you commit code.
2) you push your code (or do a pull request).
3) Github receives the push and uses it's webhook to notify Jenkins via a tunnel created by ngrok (because we don't have a way to communicate directly with Jenkins).
4) Jenkins receives a notification that a repository included in a pipeline has received a push.
5) Jenkins pulls every change to the repository in Jenkins workspace.
6) Jenkins starts the pipeline associated with that repository.
7) The Pipeline builds the project.
8) The Pipeline Runs the tests while doing code coverage.
9) The Pipeline shows build status and tests reports.
10) Jenkins notifies Github the results of the pipeline build.

Looks easy, right? The only problem is understanding that Jenkins is meant to be used in a server, which means that it (and every
 appication that the pipeline invokes) has to work in headless mode. Also, no application invoked has to have any input allowed.

This problem is a source of some headaches in the beginning, but you'll become accustomed to it.

First Time Steps:

0) Install required programs.
1) Create Unreal Project.
2) Add .gitignore.
3) Add Jenkinsfile and push changes.
4) Create a class (without parent, None) from the UE Editor, place it in a separate 'Tests' folder and use it as a test class.
5) Create tests.
6) In Jenkins Install:
  -Blue Ocean plugin (there're plugins necessary with it and if you want a prettier Jenkins).
  -GitHub plugin (for pull requests).
  -HTTP request plugin (mm don't know if necessary, but it was some time ago).
  -Cobertura plugin (for code coverage).
  -Slack plugin and configure it (if you want slack notifications).
7) Create Jenkins Multibranch Pipeline project.
8) Create a tunnel via ngrok to the Jenkins port (default is 8080).
9) Add a webhook to the github repository referencing the http given by ngrok (don't forget to add a forward slash '/' to the webhook trail if it doesn't have one!!!).
10) Push to see the build trigger in Jenkins.

It would be nice to add github checks to pull requests, but it's not possible with a free account.


Jenkinsfile:

- I use node 'master' because I have only one pc for Jenkins.
- I use a custom workspace (and at the beginning of the disk) because the Unreal Build Tool has problems with long filenames.
- The environment variables are used as parameters, to avoid hardcoding.
- BuildWithoutCooking.bat it's used to build the project. I don't use cooking because I think that process should be made when in production.
- It's not necessary to create the Visual Studio files because we don't do anything with Visual Studio, we run the tests using the Unreal Automation Tool.
- TestRunnerAndCodeCoverage uses OpenCppCodeCoverage (which does the code coverage) attached to the Unreal Engine Editor (which does the tests run).
- The Tests Report is made in JSon so we need to parse it to XML to be readable by JUnit.
- The CodeCoverageReport will be used by Cobertura to display the code coverage.
- In some places, slackSend is used to send messages to a Slack Workspace. The channel name is only used if you want to override the one used in the Slack plugin configuration.
- I do a git hard reset and git clean to clean the workspace after everything has been done. This way, if the repository it's something big, only the changes are downloaded and thus, we save bandwidth.
- Thanks to Michael Delva for his test report parser method found in his blogspot: https://www.emidee.net/ue4/2018/11/13/UE4-Unit-Tests-in-Jenkins.html, I used it almost with no changes.
