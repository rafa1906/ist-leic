package m19;

import java.util.List;
import java.util.ArrayList;

public class StringSearch implements Search {

    @Override
    public boolean searchInBook(Book book, String s) {
        return book.getAuthor().toLowerCase().contains(s.toLowerCase()) ||
               book.getTitle().toLowerCase().contains(s.toLowerCase());
    }

    @Override
    public boolean searchInDVD(DVD dvd, String s) {
        return dvd.getDirector().toLowerCase().contains(s.toLowerCase()) ||
               dvd.getTitle().toLowerCase().contains(s.toLowerCase());
    }

    @Override
    public String searchInLibrary(Library lib, String s) {
        List<Work> sortedWorks = new ArrayList<>();
        List<Work> allWorks = new ArrayList<>(lib.getWorks().values());
        String formattedWorks = "";
        
        for (Work work: allWorks){
            if(work.beSearched(this, s))
                sortedWorks.add(work);
        }
    
        for (Work work: sortedWorks)
            formattedWorks += work + "\n";
    
        return formattedWorks;
    
    }
    
}