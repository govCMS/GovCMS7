#!/usr/bin/env bash

# Define the script directory and our temporary directory.
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
DEPLOY='/tmp/deploy'

# Git sources
GITHUB_SOURCE_SLUG='govCMS/govCMS'
GITHUB_SOURCE="git@github.com:${GITHUB_SOURCE_SLUG}.git"
GITHUB_BRANCH='master'

# Mirrors
declare -A MIRRORS
MIRRORS['govcms@git.drupal.org:project/govcms.git']='7.x-2.x'

add_key() {
  # Decrypt the key we've stored in the repo and add it to our friendly ssh agent.
  openssl aes-256-cbc -K "$encrypted_16038e47068b_key" -iv "$encrypted_16038e47068b_iv" -in "${DIR}/govcms_rsa.enc" -out "${DIR}/govcms_rsa" -d
  chmod 600 "${DIR}/govcms_rsa"
  eval "$(ssh-agent -s)"
  ssh-add "${DIR}/govcms_rsa"
}

mirror_push() {
  # Clone HEAD of master branch from govCMS source.
  git clone --branch=${GITHUB_BRANCH} ${GITHUB_SOURCE} ${DEPLOY}

  # Change to the repo location and iterate over remotes.
  cd ${DEPLOY}
  for REMOTE in "${!MIRRORS[@]}"; do
    # Add each remote and push our master branch to the correct remote branch.
    git remote set-url origin ${REMOTE}
    git push origin "${GITHUB_BRANCH}:${MIRRORS[$REMOTE]}"
    if [ ! -z "${TRAVIS_TAG}" ]; then
      git push origin --tags
    fi
    # Remove the remote in case we have further remotes.
  done
}

echo "Mirror Deployment"
echo "Branch: ${TRAVIS_BRANCH}"
echo "Tag:    ${TRAVIS_TAG}"
echo "PR:     ${TRAVIS_PULL_REQUEST}"
echo "Slug:   ${TRAVIS_REPO_SLUG}"

if ([ "${TRAVIS_BRANCH}" == "${GITHUB_BRANCH}" ] || [ ! -z "${TRAVIS_TAG}" ]) &&
  [ "${TRAVIS_PULL_REQUEST}" == "false" ] &&
  [ "${TRAVIS_REPO_SLUG}" == "${GITHUB_SOURCE_SLUG}" ]; then
  add_key
  mirror_push
fi

