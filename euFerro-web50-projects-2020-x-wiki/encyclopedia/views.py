from django.http import HttpResponse, HttpResponseRedirect, response
from django.shortcuts import render, redirect
from django.urls import reverse
from django import forms
import markdown2 as mk2
import random, math

from . import util

# Load list of all entries
def index(request):
    return render(request, "encyclopedia/index.html", {
        "entries": util.list_entries()
    })


# Load a page entry if it exists
def page(request, title):

    entry = util.get_entry(title)
    if not entry:
        return render(request, "encyclopedia/not_found.html")

    html = mk2.markdown(entry)

    return render(request, "encyclopedia/entry.html", {
        "title": title,
        "html": html
    })

# Search for match in the "database"
def search(request):
    if request.method == "GET":
        query = request.GET.get("q")
        entry = util.get_entry(query)
        if entry:
            return redirect(f"wiki/{query}")
        else:
            results = filter(lambda entry: str.upper(query) in str.upper(entry), util.list_entries())
            return render(request, "encyclopedia/search_results.html", {
                "title": "Results",
                "results": results
            })


# Page form to create a new page entry
class NewPagePostForm(forms.Form):
    entry_title = forms.CharField(max_length=50)
    entry_content = forms.CharField(widget=forms.Textarea, max_length=3000)

def newpage(request):
    # POST page
    if request.method == "POST":
        form = NewPagePostForm(request.POST)
        # Validate post request
        if form.is_valid():
            entry_title = form.cleaned_data["entry_title"]
            entry_content = form.cleaned_data["entry_content"]

            # if entry already exists
            entry = util.get_entry(entry_title)
            if entry:
                form.add_error("entry_title", "Title already in use")
                context = {
                    "form": form
                }
                return render(request, f"encyclopedia/newpage.html", context)
            # else save entry
            util.save_entry(title=entry_title, content=entry_content)
            return redirect(f"wiki/{entry_title}")
        else:
            context = {
                "form": form
            }
            return render(request, f"encyclopedia/newpage.html", context)
    # GET page
    else:
        form = NewPagePostForm()
        context = {
            "form": form
        }
        return render(request, "encyclopedia/newpage.html", context)
    

# Page form where an article can be edited and saved
class EditPagePostForm(forms.Form):
    entry_title = forms.CharField(max_length=50)
    entry_content = forms.CharField(widget=forms.Textarea, max_length=30000)
    
def editpage(request):
    if request.method == "POST":
        form = EditPagePostForm(request.POST)
        if form.is_valid():
            entry_title = form.cleaned_data["entry_title"]
            entry_content = form.cleaned_data["entry_content"]
            # Save edited page
            util.save_entry(title=entry_title, content=entry_content)
            return redirect(f'wiki/{entry_title}')
        else:
            context = {
                "form": form,
                "content": request.POST.get("entry_content")
            }
            return render(request, "encyclopedia/editpage.html", context)

    if request.method == "GET":
        entry_title = request.GET.get("entry_title")
        entry = util.get_entry(entry_title)
        if entry:
            form = EditPagePostForm()
            context = {
                "entry_title": entry_title,
                "form": form,
                "content": entry

            }
            return render(request, "encyclopedia/editpage.html", context)
        
# Return a random page
def randompage(request):
    entries = util.list_entries()
    rand_entry = entries[(x:=(math.floor(random.random() * (len(entries)))))]
    return redirect(f"wiki/{rand_entry}")