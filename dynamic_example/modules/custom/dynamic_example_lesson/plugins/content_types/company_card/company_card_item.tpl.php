<?php

/**
 * @file
 * Company card.
 */
?>
<div class="ui card">
    <div class="content">
        <div class="right floated meta"><?php print $time_ago; ?></div>
        <img class="ui avatar image" src="<?php print $image; ?>"><?php print $title; ?>
    </div>
    <div class="image">
        <img src="<?php print $image; ?>">
    </div>
    <div class="content">
      <span class="right floated">
        <i class="heart outline like icon"></i>
        17 likes
      </span>
        <i class="comment icon"></i>
        <?php print $comment; ?>
    </div>
    <div class="extra content">
        <div class="ui large transparent left icon input">
            <i class="heart outline icon"></i>
            <input type="text" placeholder="Add Comment...">
        </div>
    </div>
</div>


