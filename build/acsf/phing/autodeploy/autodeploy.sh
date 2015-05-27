#!/bin/bash

# Define the script directory and our temporary directory.
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
DEPLOY='/tmp/deploy'

# Git sources
GITHUB_SOURCE_SLUG='govCMS/govCMS-Core'
GITHUB_SOURCE="git@github.com:${GITHUB_SOURCE_SLUG}.git"
BRANCH='master'

# Mirrors
MIRRORS=()
MIRRORS+=('git@github.com:govCMS/govCMS.git')
# @TODO uncomment this to push to d.o.
#MIRRORS+=('pkil@git.drupal.org:project/govcms.git')

add_key() {
  # Decrypt the key we've stored in the repo and add it to our friendly ssh agent.
  openssl aes-256-cbc -K "$encrypted_a306a1087d72_key" -iv "$encrypted_a306a1087d72_iv" -in "${DIR}/govcms_rsa.enc" -out "${DIR}/govcms_rsa" -d
  chmod "600 ${DIR}/govcms_rsa"
  eval "$(ssh-agent -s)"
  ssh-add "${DIR}/govcms_rsa"
}

mirror_push() {
  # Clone HEAD of master branch from govCMS source.
  git clone --branch=${BRANCH} ${GITHUB_SOURCE} ${DEPLOY}

  # Use git filter-branch to remove ACSF specifics.
  cd ${DEPLOY}
  git filter-branch --force --index-filter 'git rm -r --cached --ignore-unmatch acsf build/acsf' --prune-empty --tag-name-filter cat -- --all

  # Add our remotes & PUSH.HIM
  for key in "${!MIRRORS[@]}"; do
    git remote add "${key}" "${MIRRORS[$key]}"
    git push --tags -f "${key}" "${BRANCH}"
  done
}

echo "Mirror Deployment"
echo "Branch: ${TRAVIS_BRANCH}"
echo "Tag:    ${TRAVIS_TAG}"
echo "PR:     ${TRAVIS_PULL_REQUEST}"
echo "Slug:   ${TRAVIS_REPO_SLUG}"

if ([ "${TRAVIS_BRANCH}" == "${BRANCH}" ] || [ ! -z "${TRAVIS_TAG}" ]) &&
  [ "${TRAVIS_PULL_REQUEST}" == "false" ] &&
  [ "${TRAVIS_REPO_SLUG}" == "${GITHUB_SOURCE_SLUG}" ]; then
  add_key
  mirror_push
fi
