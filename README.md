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

Steps:

1) Create Unreal Project.
2) Add .gitignore.
3) Add Jenkinsfile.
4) Create a class (with no parent) from the UE Editor, place it in a separate 'Tests' folder and use it as a test class.

(to do)



 
Thanks to Michael Delva for his test report parser method found in his blogspot: https://www.emidee.net/ue4/2018/11/13/UE4-Unit-Tests-in-Jenkins.html
