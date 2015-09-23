---
layout: page
title: Sample Articles
excerpt: "An archive of articles sorted by date."
search_omit: true
---

<ul class="post-list">
{% for post in site.categories.articles %} 
  <li><article><a href="{{ site.url }}{{ post.url }}">{{ post.title }} {% if post.excerpt %} <span class="excerpt">{{ post.excerpt }}</span>{% endif %}</a></article></li>
{% endfor %}
</ul>
