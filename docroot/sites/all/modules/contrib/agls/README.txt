=========================================
Description
=========================================

The AGLS module extends the Meta tags (http://drupal.org/project/metatag) module
to add AGLS Metadata Standard tags.

The AGLS Metadata Standard is a set of descriptive properties to improve
visibility and availability of online resources.


=========================================
Meta tags
=========================================

aglsterms.availability
aglsterms.function
aglsterms.mandate

dcterms.audience
dcterms.contributor
dcterms.coverage
dcterms.creator
dcterms.date
dcterms.description
dcterms.format
dcterms.identifier
dcterms.language
dcterms.publisher
dcterms.relation
dcterms.rights
dcterms.source
dcterms.subject
dcterms.title
dcterms.type


=========================================
Meta tag obligation in AGLS compliance
=========================================

The AGLS standard states that metadata properties fall into one of four
obligation categories:
* Mandatory
 - dcterms:creator
 - dcterms:title
 - dcterms:date (a related term may be substituted)
* Conditional
 - aglsterms:availability (mandatory for offline resources)
 - dcterms:identifier (mandatory for online resources)
 - dcterms:publisher (mandatory for information resources - optional for descriptions of services)
* Recommended
 - aglsterms:function (if dcterms:subject is not used)
 - dcterms:description
 - dcterms:language (where the language of the resource is not English)
 - dcterms:subject (if aglsterms:function is not used)
 - dcterms:type
* Optional
 - All other properties are optional.

 
=========================================
References and further reading
=========================================

* AGLS Metadata Standard:
http://www.agls.gov.au/

* AGLS Reference Description:
http://www.agls.gov.au/pdf/AGLS%20Metadata%20Standard%20Part%201%20Reference%20Description.PDF

* AGLS Usage Guide:
http://www.agls.gov.au/pdf/AGLS%20Metadata%20Standard%20Part%202%20Usage%20Guide.PDF

* Guide to expressing AGLS metadata in XML:
http://www.agls.gov.au/pdf/Guide%20to%20expressing%20AGLS%20metadata%20in%20XML%20v1.0.PDF

* Guide to expressing AGLS metadata in rdf:
http://www.agls.gov.au/pdf/Guide%20to%20expressing%20AGLS%20metadata%20in%20RDF%20v1.0.PDF
