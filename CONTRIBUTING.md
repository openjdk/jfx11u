Contributing to OpenJFX 11 Updates
==================================

The OpenJFX 11 Updates repository is _not_ accepting new contributions. If you are looking to contribute to OpenJFX, please visit [openjdk/jfx](https://github.com/openjdk/jfx) instead.

Important bug fixes that have already been fixed in the mainline can be backported with prior approval. New fixes should first go into the mainline, and then can be considered for backporting. Approval from one of the project leads is required prior to creating the PR or integrating the fix.

To backport a fix, import the patch from the jfx mainline into a branch of your personal fork of this repo. Then, create a [Backport Pull Request](https://wiki.openjdk.java.net/display/SKARA/Backports#Backports-BackportPullRequests), by creating the PR with the title:

```
Backport LONG-COMMIT-HASH
```

where `LONG-COMMIT-HASH` is the long (40 char) commit hash of the fix as found in the main jfx repo. The Skara tooling will then note that it is a backport, and replace the title with the correct issue title.

If Skara detemines that the backport is clean, the bot will add the `clean` label and mark it as `ready` for integration. _If_ a project lead has approved
this bug for inclusion in the current update release, a review of a clean backport is optional; such a backport may be integrated without further review. If
there is any concern over the risk of the backport, please ask for a review.
