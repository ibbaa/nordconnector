pipeline {
    agent any
    tools {
        jdk "open-jdk-17"
    }
    parameters {
        gitParameter branchFilter: 'origin/(.*)', defaultValue: 'main', name: 'BRANCH', type: 'PT_BRANCH_TAG'
    }
    options {
        buildDiscarder(logRotator(numToKeepStr: '20'))
        copyArtifactPermission('deploy_nordconnector')
    }
    triggers {
        parameterizedCron('TZ=Europe/Berlin\n30 00 * * 2-7 % BRANCH=main')
    }
    stages {
        stage('checkout') {
            steps {
                checkout([$class: 'GitSCM',
                          branches: [[name: "${params.BRANCH}"]],
                          doGenerateSubmoduleConfigurations: false,
                          extensions: [],
                          gitTool: 'Default',
                          submoduleCfg: [],
                          userRemoteConfigs: [[url: 'https://github.com/ibbaa/nordconnector/']]
                        ])
            }
        }
        stage ('build') {
            steps {
                sh '$WORKSPACE/docker_build.sh'
            }
        }
    }
    post {
        success {
            archiveArtifacts artifacts: 'dockerbuild/Release/bin/*, dockerbuild/Debug/bin/*'
        }
        failure {  
            emailext subject: '$DEFAULT_SUBJECT', body: '$DEFAULT_CONTENT', replyTo: 'alwin@ibba.de', to: 'alwin.ibba@web.de'
        }  
     }  
}